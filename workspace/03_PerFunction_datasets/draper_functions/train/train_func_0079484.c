ppc32_exec_run_cpu(cpu_gen_t *gen)
{
   cpu_ppc_t *cpu = CPU_PPC32(gen);
   pthread_t timer_irq_thread;
   int timer_irq_check = 0;
   ppc_insn_t insn;
   int res;

   if (pthread_create(&timer_irq_thread,NULL,
                      (void *)ppc32_timer_irq_run,cpu))
   {
      fprintf(stderr,"VM '%s': unable to create Timer IRQ thread for CPU%u.\n",
              cpu->vm->name,gen->id);
      cpu_stop(gen);
      return NULL;
   }

   gen->cpu_thread_running = TRUE;
   cpu_exec_loop_set(gen);

 start_cpu:
   for(;;) {
      if (unlikely(gen->state != CPU_STATE_RUNNING))
         break;


      if (unlikely(cpu->irq_check))
         ppc32_trigger_irq(cpu);


      if (unlikely(cpu->ia == cpu->idle_pc)) {
         if (++gen->idle_count == gen->idle_max) {
            cpu_idle_loop(gen);
            gen->idle_count = 0;
         }
      }


      if (++timer_irq_check == cpu->timer_irq_check_itv) {
         timer_irq_check = 0;

         if (cpu->timer_irq_pending && !cpu->irq_disable &&
             (cpu->msr & PPC32_MSR_EE))
         {
            cpu->timer_irq_armed = 0;
            cpu->timer_irq_pending--;

            vm_set_irq(cpu->vm,0);

         }
      }


      cpu->tb += 100;


      ppc32_exec_fetch(cpu,cpu->ia,&insn);
      res = ppc32_exec_single_instruction(cpu,insn);


      if (likely(!res)) cpu->ia += sizeof(ppc_insn_t);
   }


   while(gen->cpu_thread_running) {
      gen->seq_state++;

      switch(gen->state) {
         case CPU_STATE_RUNNING:
            gen->state = CPU_STATE_RUNNING;
            goto start_cpu;

         case CPU_STATE_HALTED:
            gen->cpu_thread_running = FALSE;
            pthread_join(timer_irq_thread,NULL);
            break;
      }


      usleep(200000);
   }

   return NULL;
}

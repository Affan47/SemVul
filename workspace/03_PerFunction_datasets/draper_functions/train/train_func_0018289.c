cpu_start(cpu_gen_t *cpu)
{
   if (cpu) {
      cpu_log(cpu,"CPU_STATE","Starting CPU (old state=%u)...\n",cpu->state);
      cpu->state = CPU_STATE_RUNNING;
   }
}

schedule_instructions(instruction_scheduler_mode mode)
{
   int grf_count;
   if (mode == SCHEDULE_POST)
      grf_count = grf_used;
   else
      grf_count = virtual_grf_count;

   fs_instruction_scheduler sched(this, grf_count, mode);
   sched.run(&instructions);

   if (unlikely(INTEL_DEBUG & DEBUG_WM) && mode == SCHEDULE_POST) {
      printf("fs%d estimated execution time: %d cycles\n",
             dispatch_width, sched.time);
   }

   invalidate_live_intervals();
}

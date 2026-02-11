find_live_intervals(struct gl_program *prog,
                    struct interval_list *liveIntervals)
{
   GLint intBegin[REG_ALLOCATE_MAX_PROGRAM_TEMPS];
   GLint intEnd[REG_ALLOCATE_MAX_PROGRAM_TEMPS];
   GLuint i;


   if (dbg) {
      printf("Optimize: Begin find intervals\n");
   }


   if (!_mesa_find_temp_intervals(prog->Instructions, prog->NumInstructions,
                                  intBegin, intEnd))
      return GL_FALSE;


   liveIntervals->Num = 0;
   for (i = 0; i < REG_ALLOCATE_MAX_PROGRAM_TEMPS; i++) {
      if (intBegin[i] >= 0) {
         struct interval inv;
         inv.Reg = i;
         inv.Start = intBegin[i];
         inv.End = intEnd[i];
         append_interval(liveIntervals, &inv);
      }
   }


   sort_interval_list_by_start(liveIntervals);

   if (dbg) {

      for (i = 0; i < liveIntervals->Num; i++) {
         const struct interval *inv = liveIntervals->Intervals + i;
         printf("Reg[%d] live [%d, %d]:",
                      inv->Reg, inv->Start, inv->End);
         if (1) {
            GLuint j;
            for (j = 0; j < inv->Start; j++)
               printf(" ");
            for (j = inv->Start; j <= inv->End; j++)
               printf("x");
         }
         printf("\n");
      }
   }

   return GL_TRUE;
}

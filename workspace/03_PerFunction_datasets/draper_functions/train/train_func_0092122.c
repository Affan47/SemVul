print_instr_synth_amd (code_stash_t*  stash)
{
   boolean  cmpxchg8b = (BIT_EXTRACT_LE(stash->val_80000001_edx, 8, 9)
                         || BIT_EXTRACT_LE(stash->val_1_edx, 8, 9));
   boolean  cond      = (BIT_EXTRACT_LE(stash->val_80000001_edx, 15, 16)
                         || BIT_EXTRACT_LE(stash->val_1_edx, 15, 16));
   boolean  prefetch  = (BIT_EXTRACT_LE(stash->val_80000001_ecx, 8, 9)
                         || BIT_EXTRACT_LE(stash->val_80000001_edx, 29, 30)
                         || BIT_EXTRACT_LE(stash->val_80000001_edx, 31, 32));

   printf("   (instruction supported synth):\n");
   printf("      CMPXCHG8B                = %s\n", bools[cmpxchg8b]);
   printf("      conditional move/compare = %s\n", bools[cond]);
   printf("      PREFETCH/PREFETCHW       = %s\n", bools[prefetch]);
}

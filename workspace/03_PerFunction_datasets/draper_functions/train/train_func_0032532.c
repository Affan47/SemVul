oc_sb_run_bits(int _run_count){
  int i;
  for(i=0;_run_count>=OC_SB_RUN_VAL_MIN[i+1];i++);
  return OC_SB_RUN_CODE_NBITS[i];
}

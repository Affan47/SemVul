delete_all_dependences (rtx insn)
{
  sd_iterator_def sd_it;
  dep_t dep;


  for (sd_it = sd_iterator_start (insn, SD_LIST_BACK);
       sd_iterator_cond (&sd_it, &dep);)
    sd_delete_dep (sd_it);
}

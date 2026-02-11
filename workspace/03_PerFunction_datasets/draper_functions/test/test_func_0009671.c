gt_Sfxiterator_bcktab2file(FILE *fp, Sfxiterator *sfi, GtError *err)
{
  gt_error_check(err);
  gt_assert(sfi != NULL && sfi->bcktab != NULL);
  if (gt_suftabparts_numofparts(sfi->suftabparts) <= 1U)
  {
    int ret = gt_bcktab_flush_to_file(fp,sfi->bcktab,err);
    gt_fa_fclose(fp);
    return ret;
  }
  return 0;
}

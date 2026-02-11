do_sdflocdef(char *sdfloc, char *optfnam, int32 oplin_cnt)
{
 register char *chp;
 struct sdfnamlst_t *sdfp, *sdfp2, *last_sdfp;
 char *chp2;
 char fnam[IDLEN], pthnam[IDLEN];


 strcpy(pthnam, "");
 if ((chp = strchr(sdfloc, '+')) == NULL) strcpy(fnam, sdfloc);
 else
  {
   if (chp == sdfloc || chp[-1] == '\\')
    {
     chp2 = chp + 1;
     for (;;)
      {
       if ((chp = strchr(chp2, '+')) == NULL)
        { strcpy(fnam, sdfloc); goto sep_done; }

       if (chp[-1] != '\\') goto bld_both;
       chp2 = chp + 1;
      }
    }
bld_both:
   strncpy(fnam, sdfloc, chp - sdfloc);
   fnam[chp - sdfloc] = '\0';
   strcpy(pthnam, ++chp);
  }

sep_done:
 sdfp = (struct sdfnamlst_t *) __my_malloc(sizeof(struct sdfnamlst_t));
 sdfp->fnam = __pv_stralloc(fnam);
 sdfp->scopnam = __pv_stralloc(pthnam);
 sdfp->optfnam = __pv_stralloc(optfnam);
 sdfp->opt_slcnt = oplin_cnt;
 sdfp->sdfnamnxt = NULL;
 last_sdfp = NULL;


 for (sdfp2 = __sdflst; sdfp2 != NULL; sdfp2 = sdfp2->sdfnamnxt)
  last_sdfp = sdfp2;
 if (last_sdfp == NULL) __sdflst = sdfp; else last_sdfp->sdfnamnxt = sdfp;
 if (strcmp(sdfp->scopnam, "") == 0)
  {
   if (__verbose)
    {
     __cv_msg(
      "  Delay annotation values read from SDF 3.0 file \"%s\" design context.\n",
      sdfp->fnam);
    }
  }
 else
  {
   if (__verbose)
    {
     __cv_msg(
      "  Delay annotation values read from SDF 3.0 file \"%s\" scope context %s.\n",
     sdfp->fnam, sdfp->scopnam);
    }
  }
}

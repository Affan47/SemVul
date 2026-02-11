__to_vpionam(char *s, word32 vpioval)
{
 if (vpioval < 1) goto outofrng;
 if (vpioval < NVOTYPS)
  {
   strcpy(s, onames_vpi[vpioval].vpiobjnam);
   return(s);
  }
 if (vpioval >= CV_START_ONUMS && vpioval < (CV_START_ONUMS + CV_NVOTYPS))
  {
   strcpy(s, cv_onames_vpi[vpioval - CV_START_ONUMS].vpiobjnam);
   return(s);
  }

outofrng:
 sprintf(s, "**out of range (%lu)", vpioval);
 return(s);
}

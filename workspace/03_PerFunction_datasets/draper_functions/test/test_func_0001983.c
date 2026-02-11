expand_hier_files(struct cfglib_t *lbp, struct libel_t *lbep,
 struct xpndfile_t *xfp_hd)
{
 char dirstr[RECLEN];
 char bpath[RECLEN];
 char tmp[RECLEN];
 int32 first;


 if (xfp_hd->wildcard)
  {
   find_hier(lbep, xfp_hd, NULL, NULL);
   return;
  }
 first = TRUE;

 getcwd(dirstr, RECLEN);
 strcpy(bpath, "");
 while (!xfp_hd->wildcard && xfp_hd->incall != TRUE)
  {
   if (chdir(xfp_hd->fpat) < 0)
    {
     if (first)
      {
       __pv_ferr(3564, "config library %s no such directory %s\n",
       lbp->lbname, xfp_hd->fpat);
      }
     else
      {
       __pv_ferr(3564, "config library %s no such directory %s/%s\n",
        lbp->lbname, bpath, xfp_hd->fpat);
       chdir(dirstr);
       return;
      }
    }

   if (first)
    {
     strcpy(bpath, xfp_hd->fpat);
     first = FALSE;
    }
   else
    {
     strcpy(tmp, bpath);
     sprintf(bpath, "%s/%s", tmp, xfp_hd->fpat);
    }
   xfp_hd = xfp_hd->xpfnxt;
  }

 find_hier(lbep, xfp_hd, bpath, NULL);

 chdir(dirstr);
}

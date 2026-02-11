savelofig(lofig_list *ptfig)
{
   if ((!strcmp(OUT_LO, "hns")) || (!strcmp(OUT_LO, "fne"))
         || (!strcmp(OUT_LO, "hdn")) || (!strcmp(OUT_LO, "fdn")))
      vtisavelofig(ptfig);
   else if ((!strcmp(OUT_LO, "al")) || (!strcmp(OUT_LO, "alx")))
      alcsavelofig(ptfig);
   else if (!strcmp(OUT_LO, "spi")  || !strcmp( OUT_LO, "sp" ) ||
                !strcmp(OUT_LO, "cir"))
      spicesavelofig(ptfig);
   else if (!strcmp(OUT_LO, "edi"))
      edifsavelofig(ptfig);
   else if (!strcmp(OUT_LO, "vst"))
      vhdlsavelofig(ptfig);
   else if (!strcmp(OUT_LO, "cct"))
      hilosavelofig(ptfig);
        else if (!strcmp(OUT_LO, "vlg"))
                vlogsavelofig(ptfig);
   else {
      (void)fflush(stdout);
      (void)fprintf(stderr, "*** mbk error ***\n");
      (void)fprintf(stderr, "MBK_OUT_LO : %s unknown format\n", OUT_LO);
      EXIT(1);
   }
}

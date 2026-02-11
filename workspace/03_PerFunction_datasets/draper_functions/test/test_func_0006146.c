lemitcon(k)
register int k;
   {
   register int i, j;
   register char *s;
   int csbuf[CsetSize];
   union {
      char ovly[1];
      long l;
      double f;
      } x;

   if (lctable[k].c_flag & F_RealLit) {

      #ifdef Double

         int *rp, *rq;
         rp = (int *) &(x.f);
         rq = (int *) &(lctable[k].c_val.rval);
         *rp++ = *rq++;
         *rp = *rq;
      #else
         x.f = lctable[k].c_val.rval;
      #endif

      #ifdef DeBugLinker
         if (Dflag) {
            fprintf(dbgfile,"%ld:\t%d\t\t\t\t# real(%g)",(long)pc,T_Real, x.f);
            dumpblock(x.ovly,sizeof(double));
            }
      #endif

      outword(T_Real);

      #ifdef Double
         #if WordBits != 64

            outword(0);
            #ifdef DeBugLinker
               if (Dflag)
	          fprintf(dbgfile,"\t0\t\t\t\t\t# padding\n");
            #endif
         #endif
      #endif

      outblock(x.ovly,sizeof(double));
      }
   else if (lctable[k].c_flag & F_CsetLit) {
      for (i = 0; i < CsetSize; i++)
         csbuf[i] = 0;
      s = &lsspace[lctable[k].c_val.sval];
      i = lctable[k].c_length;
      while (i--) {
         Setb(*s, csbuf);
         s++;
         }
      j = 0;
      for (i = 0; i < 256; i++) {
         if (Testb(i, csbuf))
           j++;
         }

      #ifdef DeBugLinker
         if (Dflag) {
            fprintf(dbgfile, "%ld:\t%d\n",(long) pc, T_Cset);
            fprintf(dbgfile, "\t%d\n",j);
            }
      #endif

      outword(T_Cset);
      outword(j);
      outblock((char *)csbuf,sizeof(csbuf));

      #ifdef DeBugLinker
         if (Dflag)
            dumpblock((char *)csbuf,CsetSize);
      #endif

      }
   }

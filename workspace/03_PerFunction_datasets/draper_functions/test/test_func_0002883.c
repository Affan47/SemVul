shift_ins()
{
   int j;


   if (!tss.c_idx && tss.c_len >= PH_SHIFT_N) {
     tss.c_len--;
   }
   else
   if (tss.c_len >= PH_SHIFT_N) {
     int ofs;


     int fixedlen = tss.c_len - 10;
     if (fixedlen <= 0)
       fixedlen = 1;
     set_fixed(0, fixedlen);

     ofs = 1;
     putbuf(ofs);

     tss.ph_sta-=ofs;
     for(j=0; j < tss.c_len - ofs; j++) {
       tss.chpho[j] = tss.chpho[j+ofs];
#if 0
	   if (!(tss.chpho[j].flag & FLAG_CHPHO_PHO_PHRASE))
		 tss.chpho[j].ch = tss.chpho[j].cha;
#endif
     }
     tss.c_idx-=ofs;
     tss.c_len-=ofs;
     prbuf();
   }


   init_chpho_i(tss.c_len);

   if (tss.c_idx < tss.c_len) {
     for(j=tss.c_len-1; j>=tss.c_idx; j--) {
       tss.chpho[j+1] = tss.chpho[j];
#if 0
	   if (!(tss.chpho[j+1].flag & FLAG_CHPHO_PHO_PHRASE)) {
		 tss.chpho[j+1].ch = tss.chpho[j+1].cha;

	   }
#endif
     }
   }

   tss.c_len++;
   compact_win0();

#if 0
   prbuf();
   dbg("leave shift_ins\n");
#endif
}

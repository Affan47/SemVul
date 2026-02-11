rmdesc_(full)
integer full;
{

   logical ret_val, L__1;


   integer i, ra;


   ret_val = TRUE_;

   if (prsvec_1.prso < xsrch_1.xmin) {
      goto L50;
   }

   screen_1.fromdr = prsvec_1.prso;

   prsvec_1.prso = 0;

L50:
   if (play_1.here == advs_1.aroom[aindex_1.player - 1]) {
      goto L100;
   }

   rspeak_(2);

   prsvec_1.prsa = vindex_1.walkiw;

   return ret_val;

L100:
   if (lit_(play_1.here)) {
      goto L300;
   }

   rspeak_(430);

   ret_val = FALSE_;
   return ret_val;

L300:
   ra = rooms_1.ractio[play_1.here - 1];

   if (full == 1) {
      goto L600;
   }

   i = rooms_1.rdesc2[play_1.here - 1];

   if (full == 0 && (findex_1.superf || (rooms_1.rflag[play_1.here - 1] &
               RSEEN) != 0 && findex_1.brieff)) {
      goto L400;
   }


   i = rooms_1.rdesc1[play_1.here - 1];

   if (i != 0 || ra == 0) {
      goto L400;
   }

   prsvec_1.prsa = vindex_1.lookw;

   if (! rappli_(ra)) {
      goto L100;
   }

   prsvec_1.prsa = vindex_1.foow;

   goto L500;

L400:
   rspeak_(i);

L500:
   if (advs_1.avehic[play_1.winner - 1] != 0) {
      rspsub_(431, objcts_1.odesc2[advs_1.avehic[play_1.winner - 1] -
            1]);
   }

L600:
   if (full != 2) {
      L__1 = full != 0;
      princr_(L__1, play_1.here);
   }
   rooms_1.rflag[play_1.here - 1] |= RSEEN;
   if (full != 0 || ra == 0) {
      return ret_val;
   }

   prsvec_1.prsa = vindex_1.walkiw;

   if (! rappli_(ra)) {
      goto L100;
   }

   prsvec_1.prsa = vindex_1.foow;
   return ret_val;

}

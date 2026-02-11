drop_(z)
logical z;
{

   logical ret_val;


   logical f;
   integer i, x;

   ret_val = TRUE_;

   x = objcts_1.ocan[prsvec_1.prso - 1];

   if (x == 0) {
      goto L200;
   }

   if (objcts_1.oadv[x - 1] != play_1.winner) {
      goto L1000;
   }

   if ((objcts_1.oflag2[x - 1] & OPENBT) != 0) {
      goto L300;
   }
   rspsub_(525, objcts_1.odesc2[x - 1]);

   return ret_val;

L200:
   if (objcts_1.oadv[prsvec_1.prso - 1] != play_1.winner) {
      goto L1000;
   }

L300:
   if (advs_1.avehic[play_1.winner - 1] == 0) {
      goto L400;
   }

   prsvec_1.prsi = advs_1.avehic[play_1.winner - 1];

   f = put_(1);

   prsvec_1.prsi = 0;

   return ret_val;


L400:
   newsta_(prsvec_1.prso, 0, play_1.here, 0, 0);

   if (play_1.here == rindex_1.mtree) {
      newsta_(prsvec_1.prso, 0, rindex_1.fore3, 0, 0);
   }
   scrupd_(objcts_1.ofval[prsvec_1.prso - 1]);

   objcts_1.ofval[prsvec_1.prso - 1] = 0;

   objcts_1.oflag2[prsvec_1.prso - 1] |= TCHBT;

   if (objact_()) {
      return ret_val;
   }

   i = 0;

   if (prsvec_1.prsa == vindex_1.dropw) {
      i = 528;
   }
   if (prsvec_1.prsa == vindex_1.throww) {
      i = 529;
   }
   if (i != 0 && play_1.here == rindex_1.mtree) {
      i = 659;
   }
   rspsub_(i, objcts_1.odesc2[prsvec_1.prso - 1]);
   return ret_val;

L1000:
   rspeak_(527);

   return ret_val;

}

cnv_1is_to_16is(struct gate_t *gp, int32 numinsts, int32 opck, int32 npck)
{
 register int32 ii, i;
 union del_u sav_du;
 word64 ntim[16];

 for (i = 0; i < 4; i++) ntim[i] = 0ULL;
 sav_du = gp->g_du;

 create_disv(gp, numinsts, 16, ntim, npck);

 for (ii = 0; ii < numinsts; ii++)
  {
   for (i = 1; i < 16; i++)
    {
     if (i == 5 || i == 10) continue;

     if (opck == 1) ntim[i] = (word64) sav_du.dis1v1[ii];
     else if (opck == 2) ntim[i] = (word64) sav_du.dis1v2[ii];
     else ntim[i] = sav_du.dis1v[ii];
    }
   if (npck == 1)
    {
     for (i = 0; i < 16; i++)
      gp->g_du.dis16v1[16*ii + i] = (byte) ntim[i];
    }
   else if (npck == 2)
    {
     for (i = 0; i < 16; i++)
      gp->g_du.dis16v2[16*ii + i] = (hword) ntim[i];
    }
   else
    { for (i = 0; i < 16; i++) gp->g_du.dis16v[16*ii + i] = ntim[i]; }
  }
 if (opck == 1) __my_free((char *) sav_du.dis1v1, numinsts);
 else if (opck == 2) __my_free((char *) sav_du.dis1v2, 2*numinsts);
 else __my_free((char *) sav_du.dis1v, sizeof(word64)*numinsts);
}

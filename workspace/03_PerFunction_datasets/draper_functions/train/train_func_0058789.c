updatevolume (lrs_dic * P, lrs_dat * Q)
{
  lrs_mp tN, tD, Vnum, Vden;
  lrs_alloc_mp(tN); lrs_alloc_mp(tD); lrs_alloc_mp(Vnum); lrs_alloc_mp(Vden);
  rescaledet (P, Q, Vnum, Vden);
  copy (tN, Q->Nvolume);
  copy (tD, Q->Dvolume);
  linrat (tN, tD, ONE, Vnum, Vden, ONE, Q->Nvolume, Q->Dvolume);
  if (Q->debug)
    {
      prat ("\n*Volume=", Q->Nvolume, Q->Dvolume);
      pmp (" Vnum=", Vnum);
      pmp (" Vden=", Vden);
    }
  lrs_clear_mp(tN); lrs_clear_mp(tD); lrs_clear_mp(Vnum); lrs_clear_mp(Vden);

}

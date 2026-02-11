FDKsbrEnc_UpdateHiRes(UCHAR *h_hires, INT *num_hires,UCHAR * v_k_master,
            INT num_master , INT *xover_band, SR_MODE drOrSr,
            INT noQMFChannels)
{
  INT i;
  INT divider;
  INT max1,max2;


  divider = (drOrSr == DUAL_RATE) ? 2 : 1;

  if( (v_k_master[*xover_band] > (noQMFChannels/divider) ) ||
      ( *xover_band > num_master ) )  {


    max1=0;
    max2=num_master;
    while( (v_k_master[max1+1] < (noQMFChannels/divider)) &&
           ( (max1+1) < max2) )
      {
        max1++;
      }

    *xover_band=max1;
  }

  *num_hires = num_master - *xover_band;
  for(i = *xover_band; i <= num_master; i++)
    {
      h_hires[i - *xover_band] = v_k_master[i];
    }

  return (0);
}

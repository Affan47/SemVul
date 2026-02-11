brute_awa(uint16_t but, uint16_t somme, uint8_t lng)
{
  uint8_t p;
  static uint8_t const tbl_car[]={'0','1','2','3','4','5','6'};

  if (lng==0)
    return (but==somme);
  else
      for (p=0;p<4;p++)
	  if (brute_awa(but, rol(somme) + tbl_car[p], lng-1))
	    {
	      awa_res[awa_pos++]=tbl_car[p];
	      return 1;
	    }
  return 0;
}

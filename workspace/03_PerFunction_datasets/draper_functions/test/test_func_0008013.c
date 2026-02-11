acEncodeBin0(ac_encoder *ace, ac_model *acm)
  {
  ace->low += (((ace->high - ace->low + 1) * acm->cfreq[1]) / acm->cfreq[0]);

  while(1)
    {
    if(ace->high < Half)
      bit_plus_follow(ace, 0);
    else if(ace->low > HalfL1)
      {
      bit_plus_follow(ace, 1);
      ace->low -= Half, ace->high -= Half;
      }
    else if(ace->low > First_qtrL1 && ace->high < Third_qtr)
      ++ace->fbits, ace->low -= First_qtr, ace->high -= First_qtr;
    else
      break;

    ace->low <<= 0x1, ace->high <<= 0x1, ace->high |= 0x1;
    }
  }

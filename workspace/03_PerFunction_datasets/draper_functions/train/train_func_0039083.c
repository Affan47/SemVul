acEncode2(ac_encoder *ace, ac_model *acm)
  {
  uint64_t ran = (uint64_t) (ace->high-ace->low) + 1;
  ace->high    = ace->low + (ran*acm->cfreq[2]) / acm->cfreq[0] - 1;
  ace->low    += (          (ran*acm->cfreq[3]) / acm->cfreq[0]   );

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

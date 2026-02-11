quotient (const ACE_UINT64 dividend,
                     const ACE_UINT32 divisor,
                     ACE_Stats_Value &quotient)
{

  quotient.whole (static_cast<ACE_UINT32> (divisor == 0
                                           ?  0  :  dividend / divisor));

  if (quotient.precision () > 0  ||  divisor == 0)
    {
      const ACE_UINT32 field = quotient.fractional_field ();


      quotient.fractional (static_cast<ACE_UINT32> (
                             dividend % divisor * field / divisor));
    }
  else
    {


      quotient.fractional (0);
    }
}

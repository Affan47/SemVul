confp3(double pval, int *kexp, int *kmant, int kbits, int kround)
{


  double rpowref;
  double zref, zeps;
  int iexp, isign;
  int iround;

  extern const double _pow16tab[71];


  iround = kround;
  if ( iround != 0 && iround != 1 )
    {
      Error("Invalid conversion type = %d", iround);


     iround = 1;
    }


  if ( ! (fabs(pval) > 0))
    {
      *kexp  = 0;
      *kmant = 0;
      iexp   = 0;
      isign  = 0;
      goto LABEL900;
    }


  zeps = 1.0e-12;
  if ( kbits == 32 ) zeps = 1.0e-8;
  zref = pval;


  isign = 0;
  if ( zref < 0.0 )
    {
      isign = 128;
      zref  = - zref;
    }


  iexp = (int) (log(zref)/log(16.0) + 65.0 + zeps);


  if ( iexp < 0   ) iexp = 0;
  if ( iexp > 127 ) iexp = 127;


  if ( (iexp - 70) < 0 )
    rpowref = zref * _pow16tab[-(iexp - 70)];
  else
    rpowref = zref / _pow16tab[(iexp - 70)];


  if ( iround == 0 )
    {


      if ( isign == 0 )
	*kmant = (int) rpowref;
      else
	*kmant = NINT(rpowref + 0.5);
    }
  else
    {


      *kmant = NINT(rpowref);
    }


  if ( *kmant > 16777215 )
    {

    LABEL350:

      ++iexp;


      if ( iexp > 127 )
	{
          Message("Exponent overflow");
          Message("Original number = %30.20f", pval);
          Message("Sign = %3d, Exponent = %3d, Mantissa = %12d",
		  isign, iexp, *kmant);

	  Error("Exponent overflow");


          Message("Value arbitrarily set to zero.");
          *kexp  = 0;
          *kmant = 0;
          iexp  = 0;
          isign = 0;
          goto LABEL900;
	}

      if ( (iexp - 70) < 0 )
	rpowref = zref * _pow16tab[-(iexp - 70)];
      else
	rpowref = zref / _pow16tab[(iexp - 70)];

      if ( iround == 0 )
	{


	  if ( isign == 0 )
	    *kmant = (int) rpowref;
	  else
	    *kmant = NINT(rpowref + 0.5);
	}
      else
	{


	  *kmant = NINT(rpowref);
	}


      if ( *kmant > 16777215 ) goto LABEL350;
    }


  *kexp = iexp + isign;


LABEL900:


  return;
}

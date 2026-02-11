ColorDodge(const MagickRealType Sca,
  const MagickRealType Sa, const MagickRealType Dca,const MagickRealType Da)
{
#if 0


  if ((Sca*Da+Dca*Sa) >= Sa*Da)
    return( Sa*Da + Sca*(1.0-Da) + Dca*(1.0-Sa) );
  return( Dca*Sa*Sa/(Sa-Sca) + Sca*(1.0-Da) + Dca*(1.0-Sa) );
#endif
#if 0


  if ((fabs(Sca-Sa) < MagickEpsilon) && (fabs(Dca) < MagickEpsilon))
    return(Sca*(1.0-Da));
  if (fabs(Sca-Sa) < MagickEpsilon)
    return(Sa*Da+Sca*(1.0-Da)+Dca*(1.0-Sa));
  return(Sa*MagickMin(Da,Dca*Sa/(Sa-Sca)));
#endif


  if ((fabs(Sca-Sa) < MagickEpsilon) && (fabs(Dca) < MagickEpsilon))
    return(Sca*(1.0-Da)+Dca*(1.0-Sa));
  if (fabs(Sca-Sa) < MagickEpsilon)
    return(Sa*Da+Sca*(1.0-Da)+Dca*(1.0-Sa));
  return(Dca*Sa*Sa/(Sa-Sca)+Sca*(1.0-Da)+Dca*(1.0-Sa));
}

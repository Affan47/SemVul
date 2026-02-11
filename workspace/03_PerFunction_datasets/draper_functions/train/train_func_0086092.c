format(MSString& aString_,MSRateFormat format_) const
{
  if (isSet()==MSFalse) { aString_=""; return aString_.string(); }
  if (isValid()==MSFalse)
   {
     aString_="?";
     MSError::error(MSError::MSFailure,"MSRate::MSRateFormat","Invalid Value");
     return aString_.string();
   }

  char buf[80];
  switch (format_)
   {
   case Decimal0:
   case Decimal1:
   case Decimal2:
   case Decimal3:
   case Decimal4:
   case Decimal5:
   case Decimal6:
   case Decimal7:
   case Decimal8:
   case CommaDecimal0:
   case CommaDecimal1:
   case CommaDecimal2:
   case CommaDecimal3:
   case CommaDecimal4:
   case CommaDecimal5:
   case CommaDecimal6:
   case CommaDecimal7:
   case CommaDecimal8: return formatReal(aString_,MSFloatFormat(format_),MSFormat::NoModifier,_real);
   case Percent0: sprintf(buf,"%.0f%%",_real*100); break;
   case Percent1: sprintf(buf,"%.1f%%",_real*100); break;
   case Percent2: sprintf(buf,"%.2f%%",_real*100); break;
   case Percent3: sprintf(buf,"%.3f%%",_real*100); break;
   case Percent4: sprintf(buf,"%.4f%%",_real*100); break;
   case Percent5: sprintf(buf,"%.5f%%",_real*100); break;
   case BasisPoint: sprintf(buf,"%.0fbp",_real*10000); break;
   default:
     MSError::error(MSError::MSFailure,"MSRate::MSRateFormat","Invalid Value");
     return format(aString_);
   }

  aString_=buf;
  return aString_.string();
}

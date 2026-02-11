asDebugInfo(void) const
{
  MSString result("MSMoney(@");
  result+=MSString((unsigned long)this).d2x().lowerCase();
  result+=",_real=";
  result+=MSString(_real);
  result+=",_isSet=";
  result+=(isSet()==MSTrue)?"MSTrue":"MSFalse";
  result+=",_isValid=";
  result+=(isValid()==MSTrue)?"MSTrue":"MSFalse";
  result+=",_currency=";
  result+=MSString((int)_currency);
  result+=",_defaultCurrency=";
  result+=MSString((int)_defaultCurrency);
  result+=",_type=";
  result+=type().symbolName();
  result+=")";
  return MSString(result);
}

get(MSAttrValueList& avList_)
{
  avList_ << MSAttrValue("monthDropDown",
			 (monthDropDown() == MSTrue) ?"MSTrue":"MSFalse",
			 MSStringVector("MSFalse\nMSTrue"));
  avList_ << MSAttrValue("comboArrowColor",
                         server()->colorName(comboArrowColor()), MSAttrValue::Color);

  avList_<<MSAttrValue("incrementValue",_incrementValue.asString(),MSAttrValue::String);
  if (_minimumValue.isSet()==MSTrue)
   {
     avList_<<MSAttrValue("minimumValue",_minimumValue.asString(),MSAttrValue::String);
   }
  else avList_<<MSAttrValue("minimumValue","",MSAttrValue::String);
  if (_maximumValue.isSet()==MSTrue)
   {
     avList_<<MSAttrValue("maximumValue",_maximumValue.asString(),MSAttrValue::String);
   }
  else avList_<<MSAttrValue("maximumValue","",MSAttrValue::String);
  return MSEntryFieldPlus::get(avList_);
}

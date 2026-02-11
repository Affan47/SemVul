operator=(const MSAttrValue& aAttrValue_)
{
  if (&aAttrValue_!=this)
   {
     _attribute=aAttrValue_._attribute;
     _value=aAttrValue_._value;
     _options=aAttrValue_._options;
     _valueType=aAttrValue_._valueType;
   }
  return *this;
}

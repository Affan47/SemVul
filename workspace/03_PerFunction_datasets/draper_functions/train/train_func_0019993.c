simpleFieldIndexValue (ComplexFieldIndex field)
{
  if (field->name != NULL)
    {
      parseComplexFieldIndex (field);
    }
  if (field->dtype != FieldIndexValue)
    {
      return InvalidFieldIndex;
    }
  else
    {
      return field->datum.index;
    }
}

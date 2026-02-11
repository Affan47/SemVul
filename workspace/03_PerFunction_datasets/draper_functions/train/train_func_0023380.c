is_default_attribute() const
{
  if (Object_attribute::attribute_type_has_int_value(this->type_)
      && this->int_value_ != 0)
    return false;
  if (Object_attribute::attribute_type_has_string_value(this->type_)
      && !this->string_value_.empty())
    return false;
  if (Object_attribute::attribute_type_has_no_default(this->type_))
    return false;

  return true;
}

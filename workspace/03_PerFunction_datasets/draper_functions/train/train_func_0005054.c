set_type( Term term, Type type )
{
  if( is_object( term ) )
    object_types_[term - first_object()] = type;
  else
    variable_types_[first_variable() - term] = type;
}

set_property( const std::string& label, const Property_base& property )
{

  property_.push_back( std::pair<std::string,Property_base*>( label, property.clone() ) );

  return true;
}

copy( const PropertyManager& mgr )
{

  for ( int i = 0; i < property_.size(); i++ ) delete property_[i].second;
  property_.clear();
  for ( int i = 0; i < mgr.property_.size(); i++ )
    property_.push_back( std::pair<std::string,Property_base*>(
      mgr.property_[i].first, mgr.property_[i].second->clone() ) );

  return *this;
}

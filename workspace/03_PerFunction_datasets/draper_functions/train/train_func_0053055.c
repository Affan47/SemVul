GetWidget( short id ) const {
  for ( vector<Widget *>::const_iterator i = components.begin();
        i != components.end(); ++i )
    if ( (*i)->ID() == id ) return *i;

  return 0;
}

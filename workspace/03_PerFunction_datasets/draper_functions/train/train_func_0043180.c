Valid( bool focus ) {
	for ( PropertyFieldsType::iterator i = propertyFields.begin(); i != propertyFields.end(); ++i )
      if ( ! (*i)->Valid() ) {
         if ( focus )
            (*i)->Focus();
         return false;
      }
	return true;
}

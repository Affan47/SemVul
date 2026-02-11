postappend(){
    if ( _parent->isinstance( Original_t ) ){
      if ( _class == "current" )
	_class = "original";
    }
    return this;
  }

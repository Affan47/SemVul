defaultannotatortype( AnnotationType::AnnotationType type,
					      const string& st ) const {
    if ( type == AnnotationType::NO_ANN ){
      return "";
    }
    map<AnnotationType::AnnotationType,multimap<string,at_t> >::const_iterator mit1 = annotationdefaults.find(type);
    string result;
    if ( mit1 != annotationdefaults.end() ){
      if ( st.empty() ){
	if ( mit1->second.size() == 1 )
	  result = mit1->second.begin()->second.t;
	return result;
      }
      else {
	if ( mit1->second.count( st ) == 1 ){
	  map<string,at_t>::const_iterator mit2 = mit1->second.find( st );
	  result = mit2->second.t;
	}
      }
    }

    return result;
  }

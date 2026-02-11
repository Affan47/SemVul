equal_key_value_pairs(const tKeyValue& kv1, const tKeyValue& kv2)const{
	if ( kv1.size() != kv2.size() )
		return false;
	for ( tKeyValue::const_iterator it1 = kv1.begin(), it2 = kv2.begin(); it1 != kv1.end(); ++it1, ++it2 ){
		if ( it1->first != it2->first ){
			return false;
		}
		if ( it1->first != "size" ){
			if ( it1->first != it2->first )
				return false;
		}
	}
	return true;
}

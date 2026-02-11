append_attrib_pair(
				HashStringValue::key_type key,
				HashStringValue::value_type value,
				Attrib_info* info) {

	if(
		(info->skip && info->skip->get(key))
		|| key.pos("line-")==0
		|| (key=="border" && !value->is_defined())
	)
		return;


	*info->tag << " " << key;
	if(value->is_string() || value->as_int()>=0)
		*info->tag << "=\"" << value->as_string() << "\"";
}

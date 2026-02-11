my_validate(pTHX_ SV* const sv, my_type_t const ref_type){
	SvGETMAGIC(sv);
	if(!check_type(sv, ref_type)){
		my_fail(aTHX_ ref_names[ref_type], sv);
	}
	return sv;
}

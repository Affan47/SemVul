check_actual_numbered_params(Value& self,
					MethodParams* actual_numbered_params) const {
	int actual_count=actual_numbered_params?actual_numbered_params->count():0;
	if(actual_count<min_numbered_params_count || actual_count>max_numbered_params_count)
		throw Exception(PARSER_RUNTIME,
			0,
			"native method of %s (%s) accepts %s %d parameter(s) (%d present)",
				self.get_class()->name_cstr(),
				self.type(),
				actual_count<min_numbered_params_count ? "minimum" : "maximum",
				actual_count<min_numbered_params_count ? min_numbered_params_count : max_numbered_params_count,
				actual_count);
}

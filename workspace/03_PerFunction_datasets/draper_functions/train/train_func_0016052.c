_if(Request& r, MethodParams& params) {
	size_t max_param=params.count()-1;
	size_t i=0;
	do {
		bool condition=params.as_bool(i, "condition must be expression", r);
		if(condition) {
			r.process_write(*params.get(i+1));
			return;
		}
		i+=2;
	} while (i < max_param);

	if(i == max_param)
		r.process_write(*params.get(i));
}

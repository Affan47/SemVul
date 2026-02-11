scapegoat_new(double a, const Comparable_vtable *data_method){
	if(a < 0.5) a = 0.5;
	if(a > 1.) a = 1.;
	scapegoat goat = {
		.size = 0,
		.max_size = 0,
		.a = a,
		.inv_log_a_inv = 1./(-log(a)),
		.data_method = data_method,
		.root = NULL
	};
	return (scapegoat*)memcpy(LINKED_MALLOC(sizeof(goat)), &goat, sizeof(goat));
}

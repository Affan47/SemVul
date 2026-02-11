hkl_pseudo_axis_engine_mode_new(
	char const *name,
	HklPseudoAxisEngineModeFunc initialize,
	HklPseudoAxisEngineModeFunc get,
	HklPseudoAxisEngineModeFunc set,
	size_t n, ...)
{
	HklPseudoAxisEngineMode *self = NULL;
	va_list ap;
	size_t i;
	size_t n_p;
	size_t n_a;
	HklFunction *functions;
	HklParameter *parameters;
	const char **axes;


	va_start(ap, n);


	functions = alloca(n * sizeof(*functions));
	for(i=0; i<n; ++i)
		functions[i] = va_arg(ap, HklFunction);


	n_p = va_arg(ap, size_t);
	parameters = alloca(n_p * sizeof(*parameters));
	for(i=0; i<n_p; ++i)
		parameters[i] = va_arg(ap, HklParameter);


	n_a = va_arg(ap, size_t);
	axes = alloca(n_a * sizeof(*axes));
	for(i=0; i<n_a; ++i)
		axes[i] = va_arg(ap, char const *);
	va_end(ap);

	self = HKL_MALLOC(HklPseudoAxisEngineMode);

	hkl_pseudo_axis_engine_mode_init(self, name, initialize, get, set,
					 n, functions,
					 n_p, parameters,
					 n_a, axes);


	return self;
}

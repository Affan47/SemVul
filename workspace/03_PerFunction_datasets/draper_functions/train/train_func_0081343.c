asn1f_process(asn1p_t *asn, enum asn1f_flags flags,
		error_logger_f error_logger) {
	arg_t arg;
	int fatals = 0;
	int warnings = 0;
	int ret;


	if(asn == NULL) {
		errno = EINVAL;
		return -1;
	}


	if(error_logger == 0) {
		error_logger = _default_error_logger;
	}

	memset(&arg, 0, sizeof(arg));
	arg.asn = asn;
	arg.eh = error_logger;

	if(flags & A1F_DEBUG) {
		arg.debug = arg.eh;
		arg.debug(-1, "Called %s() with flags %d", __func__, flags);
		flags &= ~A1F_DEBUG;
	}


	if(flags & A1F_EXTENDED_SizeConstraint) {
		arg.flags |= A1F_EXTENDED_SizeConstraint;
		flags &= ~A1F_EXTENDED_SizeConstraint;
		if(arg.debug) {
			arg.debug(-1,
				"Extended SizeConstraint support enabled");
		}
	}

	a1f_replace_me_with_proper_interface_arg = arg;


	if(flags) {
		errno = EINVAL;
		return -1;
	}


	TQ_FOR(arg.mod, &(asn->modules), mod_next) {
		ret = asn1f_fix_module__phase_1(&arg);


		if(ret == -1) fatals++;
		if(ret == 1) warnings++;
	}

	TQ_FOR(arg.mod, &(asn->modules), mod_next) {
		ret = asn1f_fix_module__phase_2(&arg);
		if(ret == -1) fatals++;
		if(ret == 1) warnings++;
	}

	memset(&a1f_replace_me_with_proper_interface_arg, 0, sizeof(arg_t));


	return fatals?-1:warnings?1:0;
}

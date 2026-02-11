validate_arithmetic(reg_t reg)
{
	if (reg.segment) {
		if (!_weak_validations)
			script_debug_flag = script_error_flag = 1;
		if (sci_debug_flags & 4)
			sciprintf("[VM] Attempt to read arithmetic value from non-zero segment [%04x]\n", reg.segment);
		return 0;
	}

	return reg.offset;
}

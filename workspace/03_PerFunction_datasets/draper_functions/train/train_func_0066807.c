signed_validate_arithmetic(reg_t reg)
{
	if (reg.segment) {
		if (!_weak_validations)
			script_debug_flag = script_error_flag = 1;
		if (sci_debug_flags & 4)
			sciprintf("[VM] Attempt to read arithmetic value from non-zero segment [%04x]\n", reg.segment);
		return 0;
	}

	if (reg.offset&0x8000)
		return (signed) (reg.offset)-65536;
	else
		return reg.offset;
}

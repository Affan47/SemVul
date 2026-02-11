ql_mask_match(uint32_t level)
{
	if (ql2xextended_error_logging == 1)
		ql2xextended_error_logging = QL_DBG_DEFAULT1_MASK;
	return (level & ql2xextended_error_logging) == level;
}

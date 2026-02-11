poldiff_enable_line_numbers(poldiff_t * diff)
{
	int retval;
	if (diff == NULL) {
		errno = EINVAL;
		return -1;
	}
	if (!diff->line_numbers_enabled) {
		if (qpol_policy_build_syn_rule_table(diff->orig_qpol))
			return -1;
		if (qpol_policy_build_syn_rule_table(diff->mod_qpol))
			return -1;
		if ((retval = avrule_enable_line_numbers(diff, AVRULE_OFFSET_ALLOW)) < 0) {
			return retval;
		}
		if ((retval = avrule_enable_line_numbers(diff, AVRULE_OFFSET_AUDITALLOW)) < 0) {
			return retval;
		}
		if ((retval = avrule_enable_line_numbers(diff, AVRULE_OFFSET_DONTAUDIT)) < 0) {
			return retval;
		}
		if ((retval = avrule_enable_line_numbers(diff, AVRULE_OFFSET_NEVERALLOW)) < 0) {
			return retval;
		}
		if ((retval = terule_enable_line_numbers(diff, TERULE_OFFSET_CHANGE)) < 0) {
			return retval;
		}
		if ((retval = terule_enable_line_numbers(diff, TERULE_OFFSET_MEMBER)) < 0) {
			return retval;
		}
		if ((retval = terule_enable_line_numbers(diff, TERULE_OFFSET_TRANS)) < 0) {
			return retval;
		}
		diff->line_numbers_enabled = 1;
	}
	return 0;
}

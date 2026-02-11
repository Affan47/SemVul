auparse_first_record(auparse_state_t *au)
{
	int rc;

	if (aup_list_get_cnt(&au->le) == 0) {
		rc = auparse_next_event(au);
		if (rc <= 0)
			return rc;
	}
	aup_list_first(&au->le);
	aup_list_first_field(&au->le);

	return 1;
}

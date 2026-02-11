adcli_enroll_set_os_version (adcli_enroll *enroll,
                             const char *value)
{
	return_if_fail (enroll != NULL);
	if (value && value[0] == '\0')
		value = NULL;
	_adcli_str_set (&enroll->os_version, value);
}

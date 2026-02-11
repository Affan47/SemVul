open_syslog(krb5_context context,
	    krb5_log_facility *facility, int min, int max,
	    const char *sev, const char *fac)
{
    struct _heimdal_syslog_data *sd = malloc(sizeof(*sd));
    int i;

    if (sd == NULL)
	return krb5_enomem(context);
    i = find_value(sev, syslogvals);
    if(i == -1)
	i = LOG_ERR;
    sd->priority = i;
    i = find_value(fac, syslogvals);
    if(i == -1)
	i = LOG_AUTH;
    sd->priority |= i;
    roken_openlog(facility->program, LOG_PID | LOG_NDELAY, i);
    return krb5_addlog_func(context, facility, min, max,
			    log_syslog, close_syslog, sd);
}

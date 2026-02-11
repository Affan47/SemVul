syslog_send ( struct interface *xfer, unsigned int severity,
		  const char *message, const char *terminator ) {

	return xfer_printf ( xfer, "<%d>%s%s%s%sipxe: %s%s",
			     SYSLOG_PRIORITY ( SYSLOG_DEFAULT_FACILITY,
					       severity ),
			     ( syslog_hostname ? syslog_hostname : "" ),
			     ( syslog_domain ? "." : "" ),
			     ( syslog_domain ? syslog_domain : "" ),
			     ( ( syslog_hostname || syslog_domain ) ? " " : ""),
			     message, terminator );
}

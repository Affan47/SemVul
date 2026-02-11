print_error(const char *str, const char *token, int type)
{
    erroneousMibs++;
    DEBUGMSGTL(("parse-mibs", "\n"));
    if (type == ENDOFFILE)
        snmp_log(LOG_ERR, "%s (EOF): At line %d in %s\n", str, mibLine,
                 File);
    else if (token && *token)
        snmp_log(LOG_ERR, "%s (%s): At line %d in %s\n", str, token,
                 mibLine, File);
    else
        snmp_log(LOG_ERR, "%s: At line %d in %s\n", str, mibLine, File);
}

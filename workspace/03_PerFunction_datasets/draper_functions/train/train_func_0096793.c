setserial_parse_config( const char *token, char *cptr )
{
    setserialno = atoi(cptr);
    setserialno++;
    DEBUGMSGTL(("snmpSetSerialNo",
                "Re-setting SnmpSetSerialNo to %d\n", setserialno));
}

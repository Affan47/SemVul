snmpv3_get_engineID(u_char * buf, size_t buflen)
{


    if (!buf || (buflen < engineIDLength)) {
        return 0;
    }
    if (!engineID) {
        return 0;
    }

    memcpy(buf, engineID, engineIDLength);
    return engineIDLength;

}

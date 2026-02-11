direct_query_respond(struct sockaddr *from, int fromlen,
                     int length, xdmOpCode type, int fd)
{
    ARRAYofARRAY8 queryAuthenticationNames;
    int expectedLen;
    int i;

    if (!XdmcpReadARRAYofARRAY8(&buffer, &queryAuthenticationNames))
        return;
    expectedLen = 1;
    for (i = 0; i < (int)queryAuthenticationNames.length; i++)
        expectedLen += 2 + queryAuthenticationNames.data[i].length;
    if (length == expectedLen)
        all_query_respond(from, fromlen, &queryAuthenticationNames, type, fd);
    XdmcpDisposeARRAYofARRAY8(&queryAuthenticationNames);
}

htonll(u_int64_t value)
{
    static int necessary = -1;


    if (necessary == -1)
        necessary = (5 != htons(5));


    if (necessary)
        return (((u_int64_t) htonl(value & 0x00000000ffffffffLL)) << 32) | ((u_int64_t) htonl(value >> 32));
    else
        return value;
}

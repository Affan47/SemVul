dimension()  const
{


    int masklength = netmask->getLength();
    int host_part = netmask->addressLengthBits() - masklength;
    if (host_part>=32) return INT_MAX;

    unsigned int u = 1;
    for (int i=0; i<host_part; ++i) u<<=1;

    return u;
}

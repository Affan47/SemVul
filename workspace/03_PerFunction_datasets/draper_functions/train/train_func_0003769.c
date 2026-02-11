operator<=(const TIPv6Addr &other)
{
    for (int i=0;i<16;i++) {
        if (Addr[i]<other.Addr[i])
            return true;
        if(Addr[i]>other.Addr[i])
	    return false;
    }
    return true;
}

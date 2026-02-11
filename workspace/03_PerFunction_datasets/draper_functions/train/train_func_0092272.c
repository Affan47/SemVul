recordpacket(int chan, void *data, int len)
{
    if(recordpackets) writedemo(chan, data, len);
}

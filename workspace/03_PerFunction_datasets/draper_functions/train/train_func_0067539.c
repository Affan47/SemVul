prefixInPool(SPtr<TIPv6Addr> prefix)
{
    SPtr<TStationRange> pool = 0;
    PoolLst.first();
    while ( pool=PoolLst.get() ) {
	if (pool->in(prefix))
	    return true;
    }
    return false;
}

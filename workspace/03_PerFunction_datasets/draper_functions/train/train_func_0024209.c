setDebugLevel(DebugLevel level)
{
	d->debugLevel = level;
	if(d->pool)
		d->pool->setDebugLevel((StunTransactionPool::DebugLevel)level);
}

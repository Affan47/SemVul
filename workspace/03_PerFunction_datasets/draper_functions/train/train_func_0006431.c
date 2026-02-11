ixgbe_fcoe_dma_pool_free(struct ixgbe_fcoe *fcoe, unsigned int cpu)
{
	struct ixgbe_fcoe_ddp_pool *ddp_pool;

	ddp_pool = per_cpu_ptr(fcoe->ddp_pool, cpu);
	dma_pool_destroy(ddp_pool->pool);
	ddp_pool->pool = NULL;
}

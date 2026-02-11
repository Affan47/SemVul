add_hwgenerator_randomness(const char *buffer, size_t count,
				size_t entropy)
{
	struct entropy_store *poolp = &input_pool;

	if (unlikely(nonblocking_pool.initialized == 0))
		poolp = &nonblocking_pool;
	else {


		wait_event_interruptible(random_write_wait,
					 kthread_should_stop() ||
			ENTROPY_BITS(&input_pool) <= random_write_wakeup_bits);
	}
	mix_pool_bytes(poolp, buffer, count);
	credit_entropy_bits(poolp, entropy);
}

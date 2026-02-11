crypto_wq_init(void)
{
	kcrypto_wq = alloc_workqueue("crypto",
				     WQ_MEM_RECLAIM | WQ_CPU_INTENSIVE, 1);
	if (unlikely(!kcrypto_wq))
		return -ENOMEM;
	return 0;
}

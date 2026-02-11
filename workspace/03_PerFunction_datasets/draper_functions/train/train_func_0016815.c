xpc_get_gru_mq_irq_uv(struct xpc_gru_mq_uv *mq, int cpu, char *irq_name)
{
	int mmr_pnode = uv_blade_to_pnode(mq->mmr_blade);

#if defined CONFIG_X86_64
	mq->irq = uv_setup_irq(irq_name, cpu, mq->mmr_blade, mq->mmr_offset,
			UV_AFFINITY_CPU);
	if (mq->irq < 0)
		return mq->irq;

	mq->mmr_value = uv_read_global_mmr64(mmr_pnode, mq->mmr_offset);

#elif defined CONFIG_IA64_GENERIC || defined CONFIG_IA64_SGI_UV
	if (strcmp(irq_name, XPC_ACTIVATE_IRQ_NAME) == 0)
		mq->irq = SGI_XPC_ACTIVATE;
	else if (strcmp(irq_name, XPC_NOTIFY_IRQ_NAME) == 0)
		mq->irq = SGI_XPC_NOTIFY;
	else
		return -EINVAL;

	mq->mmr_value = (unsigned long)cpu_physical_id(cpu) << 32 | mq->irq;
	uv_write_global_mmr64(mmr_pnode, mq->mmr_offset, mq->mmr_value);
#else
	#error not a supported configuration
#endif

	return 0;
}

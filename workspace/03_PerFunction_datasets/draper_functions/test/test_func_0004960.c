most_free_mbo_coherent(struct mbo *mbo)
{
	struct most_c_obj *c = mbo->context;
	u16 const coherent_buf_size = c->cfg.buffer_size + c->cfg.extra_len;

	dma_free_coherent(NULL, coherent_buf_size, mbo->virt_address,
			  mbo->bus_address);
	kfree(mbo);
	if (atomic_sub_and_test(1, &c->mbo_ref))
		complete(&c->cleanup);
}

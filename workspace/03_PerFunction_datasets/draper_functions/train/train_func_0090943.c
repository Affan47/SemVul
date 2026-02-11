f2fs_init_crypto(void)
{
	int res = -ENOMEM;

	f2fs_read_workqueue = alloc_workqueue("f2fs_crypto", WQ_HIGHPRI, 0);
	if (!f2fs_read_workqueue)
		goto fail;

	f2fs_crypto_ctx_cachep = KMEM_CACHE(f2fs_crypto_ctx,
						SLAB_RECLAIM_ACCOUNT);
	if (!f2fs_crypto_ctx_cachep)
		goto fail;

	f2fs_crypt_info_cachep = KMEM_CACHE(f2fs_crypt_info,
						SLAB_RECLAIM_ACCOUNT);
	if (!f2fs_crypt_info_cachep)
		goto fail;

	return 0;
fail:
	f2fs_exit_crypto();
	return res;
}

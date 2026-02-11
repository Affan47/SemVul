c4iw_uld_state_change(void *handle, enum cxgb4_state new_state)
{
	struct uld_ctx *ctx = handle;

	PDBG("%s new_state %u\n", __func__, new_state);
	switch (new_state) {
	case CXGB4_STATE_UP:
		printk(KERN_INFO MOD "%s: Up\n", pci_name(ctx->lldi.pdev));
		if (!ctx->dev) {
			int ret;

			ctx->dev = c4iw_alloc(&ctx->lldi);
			if (IS_ERR(ctx->dev)) {
				printk(KERN_ERR MOD
				       "%s: initialization failed: %ld\n",
				       pci_name(ctx->lldi.pdev),
				       PTR_ERR(ctx->dev));
				ctx->dev = NULL;
				break;
			}
			ret = c4iw_register_device(ctx->dev);
			if (ret) {
				printk(KERN_ERR MOD
				       "%s: RDMA registration failed: %d\n",
				       pci_name(ctx->lldi.pdev), ret);
				c4iw_dealloc(ctx);
			}
		}
		break;
	case CXGB4_STATE_DOWN:
		printk(KERN_INFO MOD "%s: Down\n",
		       pci_name(ctx->lldi.pdev));
		if (ctx->dev)
			c4iw_remove(ctx);
		break;
	case CXGB4_STATE_START_RECOVERY:
		printk(KERN_INFO MOD "%s: Fatal Error\n",
		       pci_name(ctx->lldi.pdev));
		if (ctx->dev) {
			struct ib_event event;

			ctx->dev->rdev.flags |= T4_FATAL_ERROR;
			memset(&event, 0, sizeof event);
			event.event  = IB_EVENT_DEVICE_FATAL;
			event.device = &ctx->dev->ibdev;
			ib_dispatch_event(&event);
			c4iw_remove(ctx);
		}
		break;
	case CXGB4_STATE_DETACH:
		printk(KERN_INFO MOD "%s: Detach\n",
		       pci_name(ctx->lldi.pdev));
		if (ctx->dev)
			c4iw_remove(ctx);
		break;
	}
	return 0;
}

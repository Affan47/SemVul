nvm_free(struct nvm_dev *dev)
{
	if (!dev)
		return;

	if (dev->mt)
		dev->mt->unregister_mgr(dev);

	kfree(dev->lptbl);
}

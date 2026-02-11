devm_kfree(struct device *dev, void *p)
{
	int rc;

	rc = devres_destroy(dev, devm_kmalloc_release, devm_kmalloc_match, p);
	WARN_ON(rc);
}

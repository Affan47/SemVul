find_ae(const char *ae_id)
{
	struct device *dev;

	WARN_ON(!ae_id);

	dev = class_find_device(hnae_class, NULL, ae_id, __ae_match);

	return dev ? cls_to_ae_dev(dev) : NULL;
}

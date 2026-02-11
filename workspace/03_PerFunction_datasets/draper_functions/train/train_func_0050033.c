driver_attach_async(void *_drv, async_cookie_t cookie)
{
	struct device_driver *drv = _drv;
	int ret;

	ret = driver_attach(drv);

	pr_debug("bus: '%s': driver %s async attach completed: %d\n",
		 drv->bus->name, drv->name, ret);
}

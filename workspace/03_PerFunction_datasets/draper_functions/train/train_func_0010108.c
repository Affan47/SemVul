driver_find(const char *name, struct bus_type *bus)
{
	struct kobject *k = kset_find_obj(bus->p->drivers_kset, name);
	struct driver_private *priv;

	if (k) {

		kobject_put(k);
		priv = to_driver(k);
		return priv->driver;
	}
	return NULL;
}

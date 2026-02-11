bus_get(struct bus_type *bus)
{
	if (bus) {
		kset_get(&bus->p->subsys);
		return bus;
	}
	return NULL;
}

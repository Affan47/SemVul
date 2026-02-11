print_addr(struct text_object *obj, char *p, int p_max_size)
{
	struct net_stat *ns = obj->data.opaque;

	if (!ns)
		return;

	if ((ns->addr.sa_data[2] & 255) == 0 &&
	    (ns->addr.sa_data[3] & 255) == 0 &&
	    (ns->addr.sa_data[4] & 255) == 0 &&
	    (ns->addr.sa_data[5] & 255) == 0) {
		snprintf(p, p_max_size, "No Address");
	} else {
		snprintf(p, p_max_size, "%u.%u.%u.%u",
		         ns->addr.sa_data[2] & 255,
		         ns->addr.sa_data[3] & 255,
		         ns->addr.sa_data[4] & 255,
		         ns->addr.sa_data[5] & 255);
	}
}

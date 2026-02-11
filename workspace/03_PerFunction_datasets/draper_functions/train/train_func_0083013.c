indi_prop_set_string(struct indi_prop_t *iprop, const char *elemname, const char *value) {
	struct indi_elem_t *ielem;
	ielem = indi_find_elem(iprop, elemname);
	if(! ielem) {
		return NULL;
	}
	strncpy(ielem->value.str, value, sizeof(ielem->value.str));
	return ielem;
}

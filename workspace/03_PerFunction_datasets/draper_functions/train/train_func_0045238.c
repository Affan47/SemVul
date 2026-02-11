hci_uint2str(hci_map *m, unsigned int val)
{
	char *str = malloc(50);
	char *ptr = str;

	if (!str)
		return NULL;

	*ptr = 0;
	while (m->str) {
		if ((unsigned int) m->val == val) {
			ptr += sprintf(ptr, "%s", m->str);
			break;
		}
		m++;
	}
	return str;
}

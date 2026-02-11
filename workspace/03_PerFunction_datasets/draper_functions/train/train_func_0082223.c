cleanup(void) {
	if (hpage_size <= 0)
		return;
	if (saved_nr_hugepages >= 0)
		set_nr_hugepages(hpage_size, saved_nr_hugepages);
	if (saved_oc_hugepages >= 0)
		set_nr_overcommit_hugepages(hpage_size, saved_oc_hugepages);
}

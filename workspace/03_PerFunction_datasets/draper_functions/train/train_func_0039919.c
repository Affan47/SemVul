_scir_print_lru_list(resource_mgr_t *mgr)
{
	int mem = 0;
	int entries = 0;
	resource_t *res = mgr->lru_first;

	while (res) {
		fprintf(stderr,"\t%s.%03d: %d bytes\n",
			sci_resource_types[res->type], res->number,
			res->size);
		mem += res->size;
		++entries;
		res = res->next;
	}

	fprintf(stderr,"Total: %d entries, %d bytes (mgr says %d)\n",
		entries, mem, mgr->memory_lru);
}

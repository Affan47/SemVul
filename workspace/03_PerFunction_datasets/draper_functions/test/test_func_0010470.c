nonstatic_release_resource_db(struct pcmcia_socket *s)
{
	struct socket_data *data = s->resource_data;
	struct resource_map *p, *q;

	for (p = data->mem_db_valid.next; p != &data->mem_db_valid; p = q) {
		q = p->next;
		kfree(p);
	}
	for (p = data->mem_db.next; p != &data->mem_db; p = q) {
		q = p->next;
		kfree(p);
	}
	for (p = data->io_db.next; p != &data->io_db; p = q) {
		q = p->next;
		kfree(p);
	}
}

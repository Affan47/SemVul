datasize()
{
	uint size=0;
	ht_view *v=first;
	while (v) {
		size+=v->datasize();
		v=v->next;
	}
	return size;
}

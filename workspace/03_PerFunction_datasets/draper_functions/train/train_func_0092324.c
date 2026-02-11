clear_array(xhash *array)
{
	unsigned i;
	hash_item *hi, *thi;

	for (i = 0; i < array->csize; i++) {
		hi = array->items[i];
		while (hi) {
			thi = hi;
			hi = hi->next;
			free(thi->data.v.string);
			free(thi);
		}
		array->items[i] = NULL;
	}
	array->glen = array->nel = 0;
}

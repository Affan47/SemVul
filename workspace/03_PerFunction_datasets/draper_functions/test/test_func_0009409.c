new_Array0(CTX ctx, size_t capacity)
{
	kArray *a = new_H(Array);
	a->dim = &dimINIT;
	a->api = &ArrayOAPI;
	a->list = NULL;
	if(capacity > 0) {
		knh_Array_grow(ctx, a, capacity, 8);
	}
	a->size = 0;
	return a;
}

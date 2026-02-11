_NewConstantArray(int n, Pointer d, Type t, Category c, int r, int *s,
		 struct constantarray_class *class)
{
    ConstantArray a = (ConstantArray) _dxf_NewArrayV(t, c, r, s,
				      (struct array_class *)class);
    if (!a)
	return NULL;


    a->array.items = n;
    if (a->array.size <= sizeof(a->array.ldata)) {
	a->data = (Pointer)a->array.ldata;
    } else {
	a->data = DXAllocate(a->array.size);
	if (!a->data)
	    return NULL;
    }
    memcpy(a->data, d, a->array.size);

    return a;
}

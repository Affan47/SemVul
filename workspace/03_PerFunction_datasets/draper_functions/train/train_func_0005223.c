merge_cylinder_type(cylinder_type_t *res, cylinder_type_t *a, cylinder_type_t *b)
{
	if (a->size.mliter)
		b = a;
	*res = *b;
}

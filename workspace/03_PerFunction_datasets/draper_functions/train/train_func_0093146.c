shared_gparam_equal (gconstpointer ka, gconstpointer kb)
{
	MonoGSharedGenericParam *p1 = (MonoGSharedGenericParam*)ka;
	MonoGSharedGenericParam *p2 = (MonoGSharedGenericParam*)kb;

	if (p1 == p2)
		return TRUE;
	if (p1->parent != p2->parent)
		return FALSE;
	if (!mono_metadata_type_equal (p1->param.param.gshared_constraint, p2->param.param.gshared_constraint))
		return FALSE;
	return TRUE;
}

brasero_io_register_with_methods (GObject *object,
                                  BraseroIOJobCallbacks *methods)
{
	BraseroIOJobBase *base;

	base = g_new0 (BraseroIOJobBase, 1);
	base->object = object;
	base->methods = methods;
	methods->ref ++;

	return base;
}

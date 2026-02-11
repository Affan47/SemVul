gog_data_allocator_editor (GogDataAllocator *dalloc, GogDataset *set,
			   int dim_i, GogDataType data_type)
{
	GogDataAllocatorClass *klass;
	g_return_val_if_fail (GOG_IS_DATA_ALLOCATOR (dalloc), NULL);

	klass = GOG_DATA_ALLOCATOR_GET_CLASS (dalloc);

	return GOG_DATA_EDITOR
		(GTK_WIDGET
		 (klass->editor (dalloc, set, dim_i, data_type)));
}

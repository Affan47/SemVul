resize_catalog(int iteration)
{
	if(iteration == current_catalog_size)
	{
		struct nvpair **temp_ptr = NULL;
		temp_ptr = realloc(global_catalog,(sizeof(*global_catalog)*current_catalog_size*2));
		if(global_catalog != temp_ptr)
		{
			global_catalog = temp_ptr;
		}
		current_catalog_size *= 2;
	}
}

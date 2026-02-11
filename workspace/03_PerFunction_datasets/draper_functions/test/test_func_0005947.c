global_catalog_cleanup()
{

	int i = 0;
	while(global_catalog[i] != NULL)
	{
		nvpair_delete(global_catalog[i]);
		i++;
	}
	free(global_catalog);
}

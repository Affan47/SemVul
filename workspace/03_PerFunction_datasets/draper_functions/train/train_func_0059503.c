Mod_LoadLighting (lump_t *l)
{
	if (!l->filelen)
	{
		loadmodel->lightdata = NULL;
		return;
	}
	loadmodel->lightdata = Hunk_Alloc ( l->filelen);
	memcpy (loadmodel->lightdata, mod_base + l->fileofs, l->filelen);
}

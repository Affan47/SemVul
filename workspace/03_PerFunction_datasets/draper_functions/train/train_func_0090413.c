free_tga(oTga * tga)
{
	if (tga) {
		if (tga->ident) {
			gdFree(tga->ident);
			tga->ident = NULL;
		}
		if (tga->bitmap) {
			gdFree(tga->bitmap);
			tga->bitmap = NULL;
		}
		gdFree(tga);
		tga = NULL;
	}
}

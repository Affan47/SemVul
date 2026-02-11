TIFFWriteDirectoryTagColormap(TIFF* tif, uint32* ndir, TIFFDirEntry* dir)
{
	static const char module[] = "TIFFWriteDirectoryTagColormap";
	uint32 m;
	uint16* n;
	int o;
	if (dir==NULL)
	{
		(*ndir)++;
		return(1);
	}
	m=(1<<tif->tif_dir.td_bitspersample);
	n=_TIFFmalloc(3*m*sizeof(uint16));
	if (n==NULL)
	{
		TIFFErrorExt(tif->tif_clientdata,module,"Out of memory");
		return(0);
	}
	_TIFFmemcpy(&n[0],tif->tif_dir.td_colormap[0],m*sizeof(uint16));
	_TIFFmemcpy(&n[m],tif->tif_dir.td_colormap[1],m*sizeof(uint16));
	_TIFFmemcpy(&n[2*m],tif->tif_dir.td_colormap[2],m*sizeof(uint16));
	o=TIFFWriteDirectoryTagCheckedShortArray(tif,ndir,dir,TIFFTAG_COLORMAP,3*m,n);
	_TIFFfree(n);
	return(o);
}

TIFFCleanup(TIFF* tif)
{


	if (tif->tif_mode != O_RDONLY)
		TIFFFlush(tif);
	(*tif->tif_cleanup)(tif);
	TIFFFreeDirectory(tif);

	if (tif->tif_dirlist)
		_TIFFfree(tif->tif_dirlist);


	while( tif->tif_clientinfo )
	{
		TIFFClientInfoLink *link = tif->tif_clientinfo;

		tif->tif_clientinfo = link->next;
		_TIFFfree( link->name );
		_TIFFfree( link );
	}

	if (tif->tif_rawdata && (tif->tif_flags&TIFF_MYBUFFER))
		_TIFFfree(tif->tif_rawdata);
	if (isMapped(tif))
		TIFFUnmapFileContents(tif, tif->tif_base, (toff_t)tif->tif_size);


	if (tif->tif_fields && tif->tif_nfields > 0) {
		uint32 i;

		for (i = 0; i < tif->tif_nfields; i++) {
			TIFFField *fld = tif->tif_fields[i];
			if (fld->field_bit == FIELD_CUSTOM &&
			    strncmp("Tag ", fld->field_name, 4) == 0) {
				_TIFFfree(fld->field_name);
				_TIFFfree(fld);
			}
		}

		_TIFFfree(tif->tif_fields);
	}

        if (tif->tif_nfieldscompat > 0) {
                uint32 i;

                for (i = 0; i < tif->tif_nfieldscompat; i++) {
                        if (tif->tif_fieldscompat[i].allocated_size)
                                _TIFFfree(tif->tif_fieldscompat[i].fields);
                }
                _TIFFfree(tif->tif_fieldscompat);
        }

	_TIFFfree(tif);
}

JPEGFixupTagsSubsampling(TIFF* tif)
{


	static const char module[] = "JPEGFixupTagsSubsampling";
	struct JPEGFixupTagsSubsamplingData m;

        _TIFFFillStriles( tif );

        if( tif->tif_dir.td_stripbytecount == NULL
            || tif->tif_dir.td_stripbytecount[0] == 0 )
        {


            return;
        }

	m.tif=tif;
	m.buffersize=2048;
	m.buffer=_TIFFmalloc(m.buffersize);
	if (m.buffer==NULL)
	{
		TIFFWarningExt(tif->tif_clientdata,module,
		    "Unable to allocate memory for auto-correcting of subsampling values; auto-correcting skipped");
		return;
	}
	m.buffercurrentbyte=NULL;
	m.bufferbytesleft=0;
	m.fileoffset=tif->tif_dir.td_stripoffset[0];
	m.filepositioned=0;
	m.filebytesleft=tif->tif_dir.td_stripbytecount[0];
	if (!JPEGFixupTagsSubsamplingSec(&m))
		TIFFWarningExt(tif->tif_clientdata,module,
		    "Unable to auto-correct subsampling values, likely corrupt JPEG compressed data in first strip/tile; auto-correcting skipped");
	_TIFFfree(m.buffer);
}

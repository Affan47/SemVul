mpo_parse_Index_IFD_entry(const guchar *tiff, guint offset,
				 guint size, TiffByteOrder bo,
				 gpointer data)
{
	guint tag;
	guint format;
	guint count;
	guint data_val;
	guint data_offset;
	guint data_length;

	MPOData *mpo = data;

	tag = tiff_byte_get_int16(tiff + offset + TIFF_TIFD_OFFSET_TAG, bo);
	format = tiff_byte_get_int16(tiff + offset + TIFF_TIFD_OFFSET_FORMAT, bo);
	count = tiff_byte_get_int32(tiff + offset + TIFF_TIFD_OFFSET_COUNT, bo);
	data_val = tiff_byte_get_int32(tiff + offset + TIFF_TIFD_OFFSET_DATA, bo);
	DEBUG_1("   tag %x format %x count %x data_val %x", tag, format, count, data_val);

        if (tag == 0xb000)
        	{
        	mpo->version = data_val;
		DEBUG_1("    mpo version %x", mpo->version);
        	}
        else if (tag == 0xb001)
        	{
        	mpo->num_images = data_val;
		DEBUG_1("    num images %x", mpo->num_images);
        	}
	else if (tag == 0xb002)
		{
		guint i;
		data_offset = data_val;
		data_length = count;
		if (size < data_offset || size < data_offset + data_length)
			{
			return -1;
			}
		if (count != mpo->num_images * 16)
			{
			return -1;
			}

		mpo->images = g_new0(MPOEntry, mpo->num_images);

		for (i = 0; i < mpo->num_images; i++) {
			guint image_attr = tiff_byte_get_int32(tiff + data_offset + i * 16, bo);
			mpo->images[i].type_code = image_attr & 0xffffff;
			mpo->images[i].representative = !!(image_attr & 0x20000000);
			mpo->images[i].dependent_child = !!(image_attr & 0x40000000);
			mpo->images[i].dependent_parent = !!(image_attr & 0x80000000);
			mpo->images[i].length = tiff_byte_get_int32(tiff + data_offset + i * 16 + 4, bo);
			mpo->images[i].offset = tiff_byte_get_int32(tiff + data_offset + i * 16 + 8, bo);
			mpo->images[i].dep1 = tiff_byte_get_int16(tiff + data_offset + i * 16 + 12, bo);
			mpo->images[i].dep2 = tiff_byte_get_int16(tiff + data_offset + i * 16 + 14, bo);

			if (i == 0)
				{
				mpo->images[i].offset = 0;
				}
			else
				{
			 	mpo->images[i].offset += mpo->mpo_offset;
			 	}

			DEBUG_1("   image %x %x %x", image_attr, mpo->images[i].length, mpo->images[i].offset);
			}
		}

	return 0;
}

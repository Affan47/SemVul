write(user_interaction & ui, generic_file & f) const
    {
        magic_number tmp;
	char tmp_ext[] = { extension_tlv, '\0' };

        tmp = htonl(magic);
        f.write((char *)&tmp, sizeof(magic));
        internal_name.dump(f);
        f.write(&flag, 1);
	if(old_header)
	{
	    if(first_size != NULL && slice_size != NULL && *first_size != *slice_size)
	    {
		tmp_ext[0] = extension_size;
		f.write(tmp_ext, 1);
		slice_size->dump(f);
	    }
	    else
	    {
		tmp_ext[0] = extension_none;
		f.write(tmp_ext, 1);
	    }
	}
	else
	{
	    f.write(tmp_ext, 1);
	    build_tlv_list(ui).dump(f);
	}
    }

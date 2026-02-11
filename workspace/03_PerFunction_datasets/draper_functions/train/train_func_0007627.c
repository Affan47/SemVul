base_from_version(const archive_version & reading_ver) const
    {
	if(reading_ver > 6)
	    return 254;
	else
	    return 256;
    }

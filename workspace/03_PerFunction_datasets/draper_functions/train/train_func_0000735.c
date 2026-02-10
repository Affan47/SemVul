get_contents(memory_file & contents) const
    {
	if(value != NULL)
	    contents.set_raw_data(*value);
	else
	    contents.set_raw_data(storage(0));
    }

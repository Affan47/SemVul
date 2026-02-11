write_hole(const infinint & length)
    {
	add_mark_at_current_position(seqt_file);
	write_as_escape(true);
	try
	{
	    length.dump(*this);
	}
	catch(...)
	{
	    write_as_escape(false);
	    throw;
	}
	write_as_escape(false);
	seen_hole = true;
    }

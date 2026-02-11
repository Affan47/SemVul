clear()
    {
	NLS_SWAP_IN;
	try
	{
	    destroy();

	    archive_option_clean_mask(x_selection);
	    archive_option_clean_mask(x_subtree);
	    x_info_details = false;
	    x_empty = false;
	    x_display_skipped = false;
	}
        catch(...)
        {
            NLS_SWAP_OUT;
            throw;
        }
        NLS_SWAP_OUT;
    }

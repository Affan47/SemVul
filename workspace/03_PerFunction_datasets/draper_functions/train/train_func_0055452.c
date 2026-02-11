get_format_name()
{
    switch (transfer_mode)
    {
    case MODE_DEFAULT:
	switch (file_rat)
	{
	case RAT_NONE:
	    return "blocks";

	default:
	    return "records";
	}
	break;

    case MODE_RECORD:
	return "records";
    case MODE_BLOCK:
	return "blocks";
    }
    return "things";
}

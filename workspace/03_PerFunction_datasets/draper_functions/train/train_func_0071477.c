fw_match_style_id(FvwmWindow *fw, style_id_t s_id)
{
	if (SID_GET_HAS_NAME(s_id))
	{
		if (matchWildcards(SID_GET_NAME(s_id), fw->class.res_class) ==
		    1)
		{
			return 1;
		}
		if (matchWildcards(SID_GET_NAME(s_id), fw->class.res_name) ==
		    1)
		{
			return 1;
		}
		if (matchWildcards(SID_GET_NAME(s_id), fw->visible_name) == 1)
		{
			return 1;
		}
		if (matchWildcards(SID_GET_NAME(s_id), fw->name.name) == 1)
		{
			return 1;
		}
		if (fw->style_name != NULL &&
		    matchWildcards(SID_GET_NAME(s_id), fw->style_name) == 1)
		{
			return 1;
		}
	}
	if (SID_GET_HAS_WINDOW_ID(s_id) &&
	    SID_GET_WINDOW_ID(s_id) == (XID)FW_W(fw))
	{
		return 1;
	}

	return 0;
}

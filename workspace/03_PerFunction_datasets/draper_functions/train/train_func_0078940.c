aenfu_candidate(fstate_src_ty *src)
{
    if (src->move)
	return 0;
    switch (src->action)
    {
    case file_action_create:
	switch (src->usage)
	{
	case file_usage_source:
	case file_usage_config:
	case file_usage_build:
	    return 1;

	case file_usage_test:
	case file_usage_manual_test:
	    break;
	}
	break;

    case file_action_modify:
    case file_action_remove:
    case file_action_insulate:
    case file_action_transparent:
	break;
    }
    return 0;
}

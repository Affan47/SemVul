_ct_get_user_api_layer_error(int error)
{
	tdsdump_log(TDS_DBG_FUNC, "_ct_get_user_api_layer_error(%d)\n", error);

	switch (error) {
	case 137:
		return  "A bind count of %1! is not consistent with the count supplied for existing binds. "
			"The current bind count is %2!.";
		break;
	case 138:
		return "Use direction CS_BLK_IN or CS_BLK_OUT for a bulk copy operation.";
		break;
	case 139:
		return "The parameter tblname cannot be NULL.";
		break;
	case 140:
		return "Failed when processing results from server.";
		break;
	case 141:
		return "Parameter %1! has an illegal value of %2!";
		break;
	case 142:
		return "No value or default value available and NULL not allowed. col = %1! row = %2! .";
		break;
	case 143:
		return "parameter name(s) must be supplied for LANGUAGE command.";
		break;
	case 16843163:
		return "This routine cannot be called when the command structure is idle.";
		break;
	default:
		break;
	}
	return "unrecognized error";
}

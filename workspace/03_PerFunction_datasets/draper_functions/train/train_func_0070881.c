gda_server_operation_op_type_to_string (GdaServerOperationType type)
{
	switch (type) {
	case GDA_SERVER_OPERATION_CREATE_DB:
		return "CREATE_DB";
	case GDA_SERVER_OPERATION_DROP_DB:
		return "DROP_DB";
	case GDA_SERVER_OPERATION_CREATE_TABLE:
		return "CREATE_TABLE";
	case GDA_SERVER_OPERATION_DROP_TABLE:
		return "DROP_TABLE";
        case GDA_SERVER_OPERATION_CREATE_INDEX:
		return "CREATE_INDEX";
        case GDA_SERVER_OPERATION_DROP_INDEX:
		return "DROP_INDEX";
        case GDA_SERVER_OPERATION_RENAME_TABLE:
		return "RENAME_TABLE";
        case GDA_SERVER_OPERATION_COMMENT_TABLE:
		return "COMMENT_TABLE";
        case GDA_SERVER_OPERATION_ADD_COLUMN:
		return "ADD_COLUMN";
        case GDA_SERVER_OPERATION_DROP_COLUMN:
		return "DROP_COLUMN";
        case GDA_SERVER_OPERATION_COMMENT_COLUMN:
		return "COMMENT_COLUMN";
	case GDA_SERVER_OPERATION_CREATE_VIEW:
		return "CREATE_VIEW";
	case GDA_SERVER_OPERATION_DROP_VIEW:
		return "DROP_VIEW";
	case GDA_SERVER_OPERATION_CREATE_USER:
		return "CREATE_USER";
	case GDA_SERVER_OPERATION_DROP_USER:
		return "DROP_USER";
	case GDA_SERVER_OPERATION_ALTER_USER:
		return "ALTER_USER";
	default:
		g_error (_("Non handled GdaServerOperationType, please report error to "
			   "http://bugzilla.gnome.org/ for the \"libgda\" product"));
		return "";
	}
}

gda_sqlite_provider_supports_operation (G_GNUC_UNUSED GdaServerProvider *provider, G_GNUC_UNUSED GdaConnection *cnc,
					GdaServerOperationType type, G_GNUC_UNUSED GdaSet *options)
{
        switch (type) {
        case GDA_SERVER_OPERATION_CREATE_DB:
        case GDA_SERVER_OPERATION_DROP_DB:

        case GDA_SERVER_OPERATION_CREATE_TABLE:
        case GDA_SERVER_OPERATION_DROP_TABLE:
        case GDA_SERVER_OPERATION_RENAME_TABLE:

        case GDA_SERVER_OPERATION_ADD_COLUMN:

        case GDA_SERVER_OPERATION_CREATE_INDEX:
        case GDA_SERVER_OPERATION_DROP_INDEX:

        case GDA_SERVER_OPERATION_CREATE_VIEW:
        case GDA_SERVER_OPERATION_DROP_VIEW:
		return TRUE;
        default:
                return FALSE;
        }
}

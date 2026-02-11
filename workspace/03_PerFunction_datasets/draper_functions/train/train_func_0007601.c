midgard_core_dbobject_private_new ()
{
	MidgardDBObjectPrivate *dbpriv = g_new (MidgardDBObjectPrivate, 1);
	dbpriv->storage_data = NULL;
	dbpriv->create_storage = NULL;
	dbpriv->update_storage = NULL;
	dbpriv->storage_exists = NULL;
	dbpriv->delete_storage = NULL;
	dbpriv->add_fields_to_select_statement = NULL;
	dbpriv->get_property = NULL;
	dbpriv->set_property = NULL;
	dbpriv->set_from_data_model = NULL;
	dbpriv->_statement_insert = NULL;
	dbpriv->_statement_insert_params = NULL;
	dbpriv->_workspace_statement_insert = NULL;
	dbpriv->_workspace_statement_insert_params = NULL;
	dbpriv->get_statement_insert = NULL;
	dbpriv->get_statement_insert_params = NULL;
	dbpriv->_statement_update = NULL;
	dbpriv->_statement_update_params = NULL;
	dbpriv->_workspace_statement_update = NULL;
	dbpriv->_workspace_statement_update_params = NULL;
	dbpriv->get_statement_update = NULL;
	dbpriv->get_statement_update_params = NULL;
	dbpriv->_statement_delete = NULL;
	dbpriv->_statement_delete_params = NULL;
	dbpriv->_workspace_statement_delete = NULL;
	dbpriv->_workspace_statement_delete_params = NULL;
	dbpriv->get_statement_delete = NULL;
	dbpriv->get_statement_delete_params = NULL;
	dbpriv->set_static_sql_select = NULL;
	dbpriv->uses_workspace = FALSE;

	return dbpriv;
}

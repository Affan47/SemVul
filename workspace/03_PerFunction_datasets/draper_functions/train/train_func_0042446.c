create_dev_map_entries( const Partition & partition, OperationDetail & operationdetail )
{


	Glib::ustring command ;
	bool exit_status = true ;


	Glib::ustring tmp = String::ucompose ( _("create missing %1 entries"), DEV_MAP_PATH ) ;
	operationdetail .add_child( OperationDetail( tmp ) );


	command = "dmraid -ay -P \"\" -v" ;
	if ( execute_command( command, operationdetail .get_last_child() ) )
	{

		command = "dmraid -ay -v" ;
		if ( execute_command( command, operationdetail .get_last_child() ) )
			exit_status = false ;
	}

	operationdetail .get_last_child() .set_status( exit_status ? STATUS_SUCCES : STATUS_ERROR ) ;

	return exit_status ;
}

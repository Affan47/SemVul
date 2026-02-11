check_repair( const Partition & partition, OperationDetail & operationdetail )
{
	exit_status = execute_command( "e2fsck -f -y -v -C 0 " + partition.get_path(), operationdetail,
				       false, true );


	return ( exit_status == 0 || exit_status == 1 || exit_status == 2 || exit_status == 256 ) ;
}

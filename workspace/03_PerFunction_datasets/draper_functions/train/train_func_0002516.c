reset_normal_vocabs( void )
{
    reset_tic_vocab( &global_voc_dict_ptr, global_voc_reset_ptr );


    do
    {
        if ( current_device_node->parent_node != NULL )
	{
	    tokenization_error( TKERROR,
		 "Missing FINISH-DEVICE for new device");
	    started_at( current_device_node->ifile_name,
		 current_device_node->line_no );
	}
	    delete_device_vocab();
    }  while ( current_device_node->parent_node != NULL );

}

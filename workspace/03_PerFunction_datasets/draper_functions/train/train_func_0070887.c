initialize_all_hmdf_table( Module_table *module_head )
{
    Hmdf_table *shmdf;
    Module_table *mpt;

    for( mpt = module_head; mpt != NULL; mpt = mpt->next ){
	if( mpt->kind != MODULE_BLOCKDATA ){
	    cut_all_hmdf_children( mpt->block_head );
	    for( shmdf = mpt->super_hmdf; shmdf != NULL; shmdf = shmdf->next ){
		shmdf->children=NULL;
	    }

	    if( mpt->kind != MODULE_MAIN )
		delete_super_hmdf( mpt );
            delete_hmdf_of_all_blocks( mpt->block_head );
	}
    }
}

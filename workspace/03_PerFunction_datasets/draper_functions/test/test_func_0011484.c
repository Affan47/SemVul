addrharvest_free( AddressHarvester *harvester ) {
	cm_return_if_fail( harvester != NULL );


	addrharvest_free_table( harvester );
	g_free( harvester->path );


	harvester->path = NULL;
	harvester->retVal = MGU_SUCCESS;
	harvester->headerTable = NULL;

	harvester->folderSize = 0;


	g_free( harvester );
}

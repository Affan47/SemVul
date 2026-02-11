IsOverviewValid( int overview_index )

{
    EstablishOverviewInfo();

    if( overview_index < 0 || overview_index >= (int) overview_infos.size() )
        ThrowPCIDSKException( "Non existant overview (%d) requested.",
                              overview_index );

    int sis_id, validity=0;

    sscanf( overview_infos[overview_index].c_str(), "%d %d",
            &sis_id, &validity );

    return validity != 0;
}

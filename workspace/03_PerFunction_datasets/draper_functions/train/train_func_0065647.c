ConsistencyCheck_DataIndices()

{
    std::string report;
    unsigned int section;

    SpaceMap smap;

    smap.AddChunk( 0, vh.header_blocks );

    for( section = 0; section < 2; section++ )
    {
        const std::vector<uint32> *map = di[section].GetIndex();
        unsigned int i;

        for( i = 0; i < map->size(); i++ )
        {
            if( smap.AddChunk( (*map)[i], 1 ) )
            {
                char msg[100];

                sprintf( msg, "Conflict for block %d, held by at least data index '%d'.\n",
                         (*map)[i], section );

                report += msg;
            }
        }

        if( di[section].bytes > di[section].block_count * block_page_size )
        {
            report += "bytes for data index to large for block count.\n";
        }
    }

    return report;
}

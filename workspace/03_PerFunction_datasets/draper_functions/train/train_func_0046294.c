CreateVirtualImageFile( int width, int height,
                                         int block_width, int block_height,
                                         eChanType chan_type,
                                         std::string compression )

{
    if( compression == "" )
        compression = "NONE";


    int img_index = CreateVirtualFile();
    SysVirtualFile *vfile = GetVirtualFile( img_index );


    PCIDSKBuffer theader(128);

    theader.Put( "", 0, 128 );

    theader.Put( width, 0, 8 );
    theader.Put( height, 8, 8 );
    theader.Put( block_width, 16, 8 );
    theader.Put( block_height, 24, 8 );
    theader.Put( DataTypeName(chan_type).c_str(), 32, 4 );
    theader.Put( compression.c_str(), 54, 8 );

    vfile->WriteToFile( theader.buffer, 0, 128 );


    int tiles_per_row = (width + block_width - 1) / block_width;
    int tiles_per_col = (height + block_height - 1) / block_height;
    int tile_count = tiles_per_row * tiles_per_col;
    int i;

    PCIDSKBuffer tmap( tile_count * 20 );

    for( i = 0; i < tile_count; i++ )
    {
        tmap.Put( -1, i*12, 12 );
        tmap.Put( 0, tile_count*12 + i*8, 8 );
    }

    vfile->WriteToFile( tmap.buffer, 128, tile_count*20 );

    return img_index;
}

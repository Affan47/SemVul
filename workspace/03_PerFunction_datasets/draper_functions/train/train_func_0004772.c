WritePCT( unsigned char pct[768] )

{
    PCIDSKBuffer seg_data;

    seg_data.SetSize( 768*4 );

    ReadFromFile( seg_data.buffer, 0, 768*4 );

    int i;
    for( i = 0; i < 256; i++ )
    {
        seg_data.Put( (int) pct[  0+i],   0+i*4, 4 );
        seg_data.Put( (int) pct[256+i],1024+i*4, 4 );
        seg_data.Put( (int) pct[512+i],2048+i*4, 4 );
    }

    WriteToFile( seg_data.buffer, 0, 768*4 );
}

DeleteSegment( int segment )

{


    PCIDSKSegment *poSeg = GetSegment( segment );

    if( poSeg == NULL )
        ThrowPCIDSKException( "DeleteSegment(%d) failed, segment does not exist.", segment );


    std::vector<std::string> md_keys = poSeg->GetMetadataKeys();
    unsigned int i;

    for( i = 0; i < md_keys.size(); i++ )
        poSeg->SetMetadataValue( md_keys[i], "" );


    segments[segment] = NULL;
    delete poSeg;


    segment_pointers.buffer[(segment-1)*32] = 'D';


    WriteToFile( segment_pointers.buffer + (segment-1)*32,
                 segment_pointers_offset + (segment-1)*32,
                 32 );
}

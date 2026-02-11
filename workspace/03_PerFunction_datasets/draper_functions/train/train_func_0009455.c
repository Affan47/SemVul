GrowBlockIndex( int section, int new_blocks )

{
    if( new_blocks == 0 )
        return;

    uint32  next_block = (uint32) (vs->GetContentSize() / block_page_size);

    while( new_blocks > 0 )
    {
        vs->di[section].AddBlockToIndex( next_block++ );
        new_blocks--;
    }

    if( GrowSection( hsec_shape, section_sizes[hsec_shape] + 4*new_blocks ) )
    {
        vs->di[sec_vert].SetDirty();
        vs->di[sec_record].SetDirty();
        vs->shape_index_page_dirty = true;
    }
}

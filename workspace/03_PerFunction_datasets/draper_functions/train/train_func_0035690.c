LoadBlocks(int requested_block_start,
                                int requested_block_count,
                                void* const buffer)
{
    if(io_handle == NULL || io_mutex == NULL)
        file->GetIODetails( &io_handle, &io_mutex );

    MutexHolder oMutex(*io_mutex);

    FlushDirtyBlock();

    unsigned int blocks_read = 0;
    unsigned int current_start = requested_block_start;

    std::size_t buffer_off = 0;

    while (blocks_read < (unsigned int)requested_block_count) {

        LoadBMEntrysTo( current_start+1 );
        unsigned int cur_segment = GetBlockSegment(current_start);

        unsigned int cur_block = current_start;
        while (cur_block < (unsigned int)requested_block_count + requested_block_start &&
               GetBlockSegment(cur_block + 1) == cur_segment) {


            cur_block++;
            LoadBMEntrysTo( cur_block+1 );
        }


        uint64 read_start = GetBlockIndexInSegment(current_start);
        uint64 read_cur = read_start * block_size;
        unsigned int count_to_read = 1;
        while (read_cur + block_size ==
               (uint64)GetBlockIndexInSegment(count_to_read + current_start) * block_size &&
            count_to_read < (cur_block - current_start) )

        {
            read_cur += block_size;
            count_to_read++;
        }

#if 0

        for (unsigned int i = 0 ; i < count_to_read; i++) {
            GrowVirtualFile(i + current_start);
        }

        printf("Coalescing the read of %d blocks\n", count_to_read);
#endif


        PCIDSKSegment *data_seg_obj =
            file->GetSegment( cur_segment );

        std::size_t data_size = block_size * count_to_read;

#if 0
        printf("Reading %d bytes at offset %d in buffer\n", data_size, buffer_off);
#endif

        data_seg_obj->ReadFromFile( ((uint8*)buffer) + buffer_off,
                                    block_size * read_start,
                                    data_size );

        buffer_off += data_size;


        current_start += count_to_read;
        blocks_read += count_to_read;
    }
}

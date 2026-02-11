mcpp_use_mem_buffers(
    int    tf
)
{
    int i;

    use_mem_buffers = tf ? TRUE : FALSE;

    for (i = 0; i < NUM_OUTDEST; ++i) {
        if (mem_buffers[ i].buffer)

            free( mem_buffers[ i].buffer);
        if (use_mem_buffers) {

            mem_buffers[ i].buffer = NULL;
            mem_buffers[ i].entry_pt = NULL;
            mem_buffers[ i].size = 0;
            mem_buffers[ i].bytes_avail = 0;
        }
    }
}

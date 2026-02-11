clear_file_state()
{

    if (mmap_start != NULL && mmap_start != MAP_FAILED)
    {
        munmap((void *)mmap_start, mmap_length);
    }
    mmap_start = NULL;
    mmap_length = 0;
    loaded_old = false;
    old_item_offsets.clear();
}

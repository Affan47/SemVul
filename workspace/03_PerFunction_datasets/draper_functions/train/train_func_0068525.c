clone_directory (struct page_directory_t *src)
{
    uint32_t phys, offset;
    int i;


    struct page_directory_t *dir = (struct page_directory_t *) kmalloc_ap (sizeof (struct page_directory_t), &phys);
    memset (dir, 0, sizeof (struct page_directory_t));


    offset = (uint32_t) dir->physical_tables - (uint32_t) dir;


    dir->physical_addr = phys + offset;


    for (i = 0; i < 1024; i++)
    {
        if (!src->tables[i])
            continue;

        if (kernel_directory->tables[i] == src->tables[i])
        {

            dir->tables[i] = src->tables[i];
            dir->physical_tables[i] = src->physical_tables[i];
        }
        else
        {

            uint32_t phys;
            dir->tables[i] = clone_table (src->tables[i], &phys);
            dir->physical_tables[i] = phys | 0x07;
        }
    }

    return dir;
}

eng_add_search_dir(char *dir)
{
    int i;
    int found_ind = -1;

    for(i=0; i<search_dirs_num; i++)
        if(! search_dirs[i]) {
            found_ind = i;
            break;
        }

    if(found_ind < 0) {
        search_dirs = util_grow_buffer_to_size(search_dirs,
                                               &search_dirs_cap,
                                               search_dirs_num+1,
                                               sizeof(*search_dirs));
        found_ind = search_dirs_num++;
    }

    i = strlen(dir) + 1;

    search_dirs[found_ind] = malloc(i);
    strcpy(search_dirs[found_ind], dir);
}

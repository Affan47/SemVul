stale_index(struct group_data *data)
{
    struct stat st;
    int r;

    r = fstat(data->indexfd, &st);
    return r == -1 && errno == ESTALE;
}

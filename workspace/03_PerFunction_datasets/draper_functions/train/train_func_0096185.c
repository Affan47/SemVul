file_skip(struct archive *a, void *client_data, off_t request)
#endif
{
    struct read_fd_data *mine = (struct read_fd_data *)client_data;
    off_t old_offset, new_offset;

    if (!mine->can_skip)
        return (0);


    request = (request / mine->block_size) * mine->block_size;
    if (request == 0)
        return (0);


    if (((old_offset = lseek(mine->fd, 0, SEEK_CUR)) < 0) ||
        ((new_offset = lseek(mine->fd, request, SEEK_CUR)) < 0))
    {

        mine->can_skip = 0;

        if (errno == ESPIPE)
        {


            return (0);
        }


        archive_set_error(a, errno, "Error seeking");
        return (-1);
    }
    return (new_offset - old_offset);
}

tgdb_recv_inferior_data(struct tgdb * tgdb, char *buf, size_t n)
{
    char local_buf[n + 1];
    ssize_t size;


    if ((size = io_read(tgdb->inferior_stdin, local_buf, n)) < 0) {
        logger_write_pos(logger, __FILE__, __LINE__, "inferior_fd read failed");
        return -1;
    }

    strncpy(buf, local_buf, size);
    buf[size] = '\0';

    return size;
}

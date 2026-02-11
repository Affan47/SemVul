isofs_read_raw_block(int block, char *buf) {
    off_t off = block * context.block_size + context.block_offset + context.file_offset;
    if(pthread_mutex_lock(& fd_mutex)) {
        int err = errno;
        perror("isofs_read_raw_block: can`l lock fd_mutex");
        return -err;
    };
    if(lseek(context.fd, off, SEEK_SET) == -1) {
        perror("isofs_read_raw_block: can`t lseek()");
        pthread_mutex_unlock(& fd_mutex);
        return -EIO;
    };
    size_t len = read(context.fd, buf, context.data_size);
    if(len != context.data_size) {
        fprintf(stderr, "isofs_read_raw_block: can`t read full block, read only %d bytes from offset %d, %Lu required; errno %d, message %s\n",
            len, (int) off, context.data_size, errno, strerror(errno));
        fprintf(stderr, "isofs_read_raw_block: huh? reading zeros beyond file end? someone want to save a penny?\n");
        memset(buf + len, 0, context.data_size - len);


    };
    pthread_mutex_unlock(& fd_mutex);

    return len;
}

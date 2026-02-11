_process_selected_fds( pcomm_context_t *context,
                            pcomm_stream_t stream,
                            fd_set        *set_ptr) {
    pcomm_fd_t *fd_context;
    list_t *stream_fds;

    int io_result;
    int *fds = NULL;
    size_t fds_len = 0;

    int i = 0;

    if (!context) {
        return;
    }
    if (context->exit_now) {
        return;
    }

    switch (stream) {
        case PCOMM_STREAM_WRITE:
            stream_fds = &context->write_fds;
            break;
        case PCOMM_STREAM_READ:
            stream_fds = &context->read_fds;
            break;
        case PCOMM_STREAM_ERROR:
            stream_fds = &context->error_fds;
            break;
    }

    if ( !_pcomm_make_fd_list(stream_fds, &fds, &fds_len) ) {
        for ( i=0; (i<fds_len) && (!context->exit_now); i++ ) {
            if ( FD_ISSET(fds[i], set_ptr) ) {
                if ( (fd_context = (pcomm_fd_t *)list_seek(stream_fds, &fds[i])) ) {

                    if (fd_context->check_only) {
                        if (context->debug) {
                            fprintf(stderr, "File descriptor %d is ready\n", fd_context->file_descriptor);
                        }
                        if (fd_context->ready_callback) {
                            fd_context->ready_callback( context,
                                                        fd_context->file_descriptor );
                        }
                    }

                    else {
                        if (stream == PCOMM_STREAM_WRITE) {
                            io_result = _write_fd( fd_context );
                            if ( fd_context->io_callback ) {
                                fd_context->io_callback( context,
                                                      fd_context->file_descriptor,
                                                      NULL, 0);
                            }
                            if ( !fd_context->buffer || !fd_context->used ) {
                                _pcomm_remove_fd( &context->write_fds,
                                                  fd_context->file_descriptor );
                                if (fd_context->close_callback) {
                                    fd_context->close_callback(context,
                                                               fd_context->file_descriptor);
                                }
                                free(fd_context);
                            }
                        }
                        else {
                            io_result = _read_fd( fd_context, context->page_size );
                            if (!io_result) {
                                fd_context->last_read_empty = 0;
                                if (fd_context->io_callback ) {
                                    fd_context->io_callback( context,
                                                          fd_context->file_descriptor,
                                                          fd_context->buffer,
                                                          fd_context->used );
                                    _pcomm_clean_read_buffer( fd_context );
                                }
                            } else if (io_result == PCOMM_NO_DATA_FROM_READ) {
                                if (fd_context->last_read_empty) {
                                    pcomm_remove_read_fd(context, fd_context->file_descriptor);
                                    if (fd_context->close_callback) {
                                        fd_context->close_callback(context,
                                                                   fd_context->file_descriptor);
                                    }
                                } else {
                                    fd_context->last_read_empty = 1;
                                }
                            }
                        }
                    }
                }
            }
        }
        free(fds);
        fds = NULL;
        fds_len = 0;
    }
}

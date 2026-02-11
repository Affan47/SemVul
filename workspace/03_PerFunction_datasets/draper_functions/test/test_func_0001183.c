libcurl_write(void *ptr, size_t size, size_t nmemb, HTTP_OP* phop) {


    size_t stWrite = fwrite(ptr, size, nmemb, phop->fileOut);
    if (log_flags.http_xfer_debug) {
        msg_printf(NULL, MSG_INFO,
            "[http_xfer] [ID#%d] HTTP: wrote %d bytes", phop->trace_id, (int)stWrite
        );
    }
    phop->bytes_xferred += (double)(stWrite);
    phop->update_speed();
    daily_xfer_history.add(stWrite, false);
    return stWrite;
}

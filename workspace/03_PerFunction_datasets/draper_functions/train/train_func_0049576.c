PR_SetLogBuffering(PRIntn buffer_size)
{
    PR_LogFlush();

    if (logBuf)
        PR_DELETE(logBuf);

    if (buffer_size >= LINE_BUF_SIZE) {
        logp = logBuf = (char*) PR_MALLOC(buffer_size);
        logEndp = logp + buffer_size;
    }
}

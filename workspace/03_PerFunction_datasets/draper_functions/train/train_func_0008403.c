prepare_aio(int d, void *buf, size_t nbytes, off_t offset)
{
    struct aiocb* aio = (struct aiocb*) malloc(sizeof(struct aiocb));
    if (aio == NULL)
        syserr("malloc\n");
    aio->aio_fildes = d;
    aio->aio_buf = buf;
    aio->aio_nbytes = nbytes;
    aio->aio_offset = offset;
    aio->aio_sigevent.sigev_notify = SIGEV_SIGNAL;
    aio->aio_sigevent.sigev_signo = SIGUSR2;
    current->aio = aio;
}

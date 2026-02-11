bwrite(int fd, void *loc, unsigned num)
{
    bool failed;

#ifdef UNIX
    if (buffering)
    {
        if(fd != bw_fd)
                panic("unbuffered write to fd %d (!= %d)", fd, bw_fd);

        failed = (fwrite(loc, (int)num, 1, bw_FILE) != 1);
    }
    else
#endif
    {

#if defined(BSD) || defined(ULTRIX)
        failed = (write(fd, loc, (int)num) != (int)num);
#else
        failed = (write(fd, loc, num) != num);
#endif
    }

    if (failed)
    {
#if defined(UNIX) || defined(VMS) || defined(__EMX__)
        if (program_state.done_hup)
                terminate(EXIT_FAILURE);
        else
#endif
                panic("cannot write %u bytes to file #%d", num, fd);
    }
}

fskip(FILE * fp, long offset, int whence)
{
#ifndef PIPE_BUF
    char    buffer[4096];
#else
    char    buffer[PIPE_BUF];
#endif


#ifndef S_ISFIFO
# ifdef _S_IFIFO

#  define	S_ISFIFO(m)	(((m)&_S_IFIFO) == _S_IFIFO)
# endif
#endif

#ifdef S_ISFIFO


    {
        int const fd = fileno(fp);
        struct stat file_stat;

        if (fstat(fd, &file_stat) == 0) {
            if (S_ISFIFO(file_stat.st_mode)) {
                if (whence != SEEK_CUR || offset < 0) {
                    return -1;
                }
                while (offset > 0) {
                    size_t const bytes_to_skip = min_size_t(sizeof(buffer), offset);
                    size_t const read = fread(buffer, 1, bytes_to_skip, fp);
                    if (read < 1) {
                        return -1;
                    }
                    offset -= read;
                }
                return 0;
            }
        }
    }
#endif
    if (0 == fseek(fp, offset, whence)) {
        return 0;
    }

    if (whence != SEEK_CUR || offset < 0) {
        if (silent < 10) {
            error_printf
                ("fskip problem: Mostly the return status of functions is not evaluate so it is more secure to polute <stderr>.\n");
        }
        return -1;
    }

    while (offset > 0) {
        size_t const bytes_to_skip = min_size_t(sizeof(buffer), offset);
        size_t const read = fread(buffer, 1, bytes_to_skip, fp);
        if (read < 1) {
            return -1;
        }
        offset -= read;
    }

    return 0;
}

zzip_dir_creat_ext_io(zzip_char_t * name, int o_mode,
                      zzip_strings_t * ext, zzip_plugin_io_t io)
{
    if (! io)
        io = zzip_get_default_io();

    if (io != zzip_get_default_io())
    {


        errno = EINVAL;
        return 0;
    }


    if (! _ZZIP_TRY)
    {


        if (! _mkdir(name, o_mode) || errno == EEXIST)
            errno = EROFS;
        return 0;
    } else
    {
#       define MAX_EXT_LEN 10
        ZZIP_DIR *dir = zzip_dir_alloc(ext);
        int name_len = strlen(name);
        dir->realname = malloc(name_len + MAX_EXT_LEN);
        if (! dir->realname)
            goto error;

        memcpy(dir->realname, name, name_len + 1);
        ___ int fd =
            __zzip_try_open(dir->realname, O_EXCL | O_TRUNC | O_WRONLY, ext,
                            io);
        if (fd != -1)
            { dir->fd = fd; return dir; }

        ___ zzip_strings_t *exx = ext;
        int exx_len;
        for (; *exx; exx++)
        {
            if ((exx_len = strlen(*exx) + 1) <= name_len &&
                ! memcmp(dir->realname + (name_len - exx_len), *exx, exx_len))
                break;
            exx++;
            if (*exx)
                continue;

            if (! (exx_len = strlen(*exx)) || exx_len >= MAX_EXT_LEN)
                break;
            memcpy(dir->realname + name_len, exx, exx_len);
        }
        ____;
        fd = (io->fd.open)(dir->realname, O_CREAT | O_TRUNC | O_WRONLY, o_mode);
        dir->realname[name_len] = '\0';
        if (fd != -1)
            { dir->fd = fd; return dir; }
      error:
        zzip_dir_free(dir);
        return 0;
        ____;
    }
}

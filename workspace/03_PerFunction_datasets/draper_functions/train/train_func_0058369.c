gnc_int_link_or_make_backup(FileBackend *be, const char *orig, const char *bkup)
{
    gboolean copy_success = FALSE;
    int err_ret =
#ifdef HAVE_LINK
        link (orig, bkup)
#else
        - 1
#endif
        ;
    if (err_ret != 0)
    {
#ifdef HAVE_LINK
        if (errno == EPERM || errno == ENOSYS
# ifdef EOPNOTSUPP
                || errno == EOPNOTSUPP
# endif
# ifdef ENOTSUP
                || errno == ENOTSUP
# endif
# ifdef ENOSYS
                || errno == ENOSYS
# endif
           )
#endif
        {
            copy_success = copy_file(orig, bkup);
        }

        if (!copy_success)
        {
            qof_backend_set_error((QofBackend*)be, ERR_FILEIO_BACKUP_ERROR);
            PWARN ("unable to make file backup from %s to %s: %s",
                   orig, bkup, g_strerror(errno) ? g_strerror(errno) : "");
            return FALSE;
        }
    }

    return TRUE;
}

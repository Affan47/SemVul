cpl_error_get_code(void)
{
    cpl_error_code code = CPL_ERROR_NONE;

#ifdef HAVE_LIBPTHREAD
    pthread_rwlock_rdlock(&cpl_lock_error_status);
#endif

    if (cpl_error_status) {
        const cpl_error * error = cpl_errorstate_find();

        code = error->code;
    }

#ifdef HAVE_LIBPTHREAD
    pthread_rwlock_unlock(&cpl_lock_error_status);
#endif

    return code;
}

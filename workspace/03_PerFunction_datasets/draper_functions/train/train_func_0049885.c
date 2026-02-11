select_checkfd(ScmObj fds)
{
    if (SCM_FALSEP(fds)) return NULL;
    if (!SCM_SYS_FDSET_P(fds))
        Scm_Error("sys-fdset object or #f is required, but got %S", fds);
    return SCM_SYS_FDSET(fds);
}

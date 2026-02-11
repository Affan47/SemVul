worker_perform(struct job *j)
{
    if (!j)
        return -1;

    switch (j->op)
    {
        case JOB_RENAME:
            return remoteop_rename(j->path, j->s1);
        case JOB_CREATE:
            return remoteop_create(j->path, j->n1, j->n2);
        case JOB_UNLINK:
            return remoteop_unlink(j->path);
        case JOB_SYMLINK:
            return remoteop_symlink(j->s1, j->path);
        case JOB_LINK:
            return remoteop_link(j->s1, j->path);
        case JOB_MKDIR:
            return remoteop_mkdir(j->path, j->n1);
        case JOB_RMDIR:
            return remoteop_rmdir(j->path);
        case JOB_CHOWN:
            return remoteop_chown(j->path, j->n1, j->n2);
        case JOB_CHMOD:
            return remoteop_chmod(j->path, j->n1);
#if HAVE_SETXATTR
        case JOB_SETXATTR:
            return remoteop_setxattr(j->path, j->s1, j->s2, j->n1, j->n2);
#endif
    }

    return -1;
}

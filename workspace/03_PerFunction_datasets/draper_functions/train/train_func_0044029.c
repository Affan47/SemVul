nlm4_lock_to_gf_flock (struct gf_flock *flock, nlm4_lock *lock, int excl)
{
        flock->l_pid = lock->svid;
        flock->l_start = lock->l_offset;
        flock->l_len = lock->l_len;
        if (excl)
                flock->l_type = F_WRLCK;
        else
                flock->l_type = F_RDLCK;
        flock->l_whence = SEEK_SET;
        nlm_copy_lkowner (&flock->l_owner, &lock->oh);
        return 0;
}

add_locks (posix_lock_t *l1, posix_lock_t *l2)
{
        posix_lock_t *sum = NULL;

        sum = GF_CALLOC (1, sizeof (posix_lock_t),
                         gf_locks_mt_posix_lock_t);
        if (!sum)
                return NULL;

        sum->fl_start = min (l1->fl_start, l2->fl_start);
        sum->fl_end   = max (l1->fl_end, l2->fl_end);

        return sum;
}

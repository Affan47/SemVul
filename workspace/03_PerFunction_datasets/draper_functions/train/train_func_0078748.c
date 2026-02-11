inodelk_type_conflict (pl_inode_lock_t *l1, pl_inode_lock_t *l2)
{
        if (l2->fl_type == F_WRLCK || l1->fl_type == F_WRLCK)
                return 1;

        return 0;
}

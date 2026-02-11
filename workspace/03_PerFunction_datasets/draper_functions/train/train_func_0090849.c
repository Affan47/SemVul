find_matching_inodelk (pl_inode_lock_t *lock, pl_dom_list_t *dom)
{
        pl_inode_lock_t *l = NULL;
        list_for_each_entry (l, &dom->inodelk_list, list) {
                if (inodelks_equal (l, lock) &&
                    same_inodelk_owner (l, lock))
                        return l;
        }
        return NULL;
}

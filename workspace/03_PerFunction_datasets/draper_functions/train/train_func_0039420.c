__grant_blocked_entry_locks (xlator_t *this, pl_inode_t *pl_inode,
                             pl_dom_list_t *dom, struct list_head *granted)
{
        int              bl_ret = 0;
        pl_entry_lock_t *bl   = NULL;
        pl_entry_lock_t *tmp  = NULL;

        struct list_head blocked_list;

        INIT_LIST_HEAD (&blocked_list);
        list_splice_init (&dom->blocked_entrylks, &blocked_list);

        list_for_each_entry_safe (bl, tmp, &blocked_list,
                                  blocked_locks) {

                list_del_init (&bl->blocked_locks);


                gf_log ("locks", GF_LOG_TRACE,
                        "Trying to unblock: {pinode=%p, basename=%s}",
                        pl_inode, bl->basename);

                bl_ret = __lock_name (pl_inode, bl->basename, bl->type,
                                      bl->frame, dom, bl->this, 0);

                if (bl_ret == 0) {
                        list_add (&bl->blocked_locks, granted);
                } else {
                        gf_log (this->name, GF_LOG_DEBUG,
                                "should never happen");
                        if (bl->basename)
                                GF_FREE ((char *)bl->basename);
                        GF_FREE (bl);
                }
        }
        return;
}

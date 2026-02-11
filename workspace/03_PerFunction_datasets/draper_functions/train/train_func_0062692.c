fd_lk_overlap (fd_lk_ctx_node_t *l1,
               fd_lk_ctx_node_t *l2)
{
        if (l1->fl_end >= l2->fl_start &&
            l2->fl_end >= l1->fl_start)
                return 1;

        return 0;
}

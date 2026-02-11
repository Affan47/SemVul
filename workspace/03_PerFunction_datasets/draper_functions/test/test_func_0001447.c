parser_release(void) {


    struct list_head_s * iter;
    list_for(&parser.top_head, iter) {
        struct list_head_s * rem_iter = iter;
        struct uish_comm_s * cmd = LIST_DATA(iter, struct uish_comm_s);
        iter = iter->prev;
        list_del(rem_iter);
        DBG(0, "free toplevel cmd: %p\n", cmd);
        uish_cmd_free_recursive(cmd);
    }
}

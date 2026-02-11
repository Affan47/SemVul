_destroy_a_que( struct list_head *que) {
    struct list_head *pos, *n;
    list_for_each_safe( pos, n, que) {
        struct my_node *n = list_entry( pos, struct my_node, head);
        list_del( pos);
        free( n);
    }
}

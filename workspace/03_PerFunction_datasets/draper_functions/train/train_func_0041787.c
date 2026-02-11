rect_list_add_split_fuzzy_and_merge(list_t *rects,
                                                list_node_t *node,
                                                int split_accepted_error,
                                                int merge_accepted_error)
{
   list_node_t *n;

   n = rect_list_add_split_fuzzy(rects, node, split_accepted_error);
   if (n && n->next)
     {
        list_t to_merge;


        to_merge.head = n->next;
        to_merge.tail = rects->tail;
        rects->tail = n;
        n->next = NULL;

        rect_list_merge_rects(rects, &to_merge, merge_accepted_error);
     }
}

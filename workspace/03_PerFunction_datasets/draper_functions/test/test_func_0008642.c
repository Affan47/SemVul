rect_list_node_pool_flush(void)
{
   while (list_node_pool.node)
     {
        list_node_t *node;

        node = list_node_pool.node;
        list_node_pool.node = node->next;
        list_node_pool.len--;

        free(node);
     }
}

rect_list_append_node(list_t *rects, list_node_t *node)
{
   if (rects->tail)
     {
	rects->tail->next = node;
	rects->tail = node;
     }
   else
     {
	rects->head = node;
	rects->tail = node;
     }
}

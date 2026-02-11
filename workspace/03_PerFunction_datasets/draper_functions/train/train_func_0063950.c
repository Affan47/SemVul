edge_list_dump (vertex_element * vertex)
{
    printf("\t#edges: %i\n", vertex->edges);
    edge_list * element = vertex->edges_head;
    while(element) {
        printf("\t\t%i-%i\n", edge_left(element->edge)->id, edge_right(element->edge)->id);
        element = element->next;
    }
}

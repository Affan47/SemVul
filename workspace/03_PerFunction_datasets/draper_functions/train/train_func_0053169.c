vertex_vertices_dump ()
{
    printf("#vertices: %i\n\n", size);
    vertex_element * element = head;
    while (element) {
        vertex_dump (element);
        element = element->next;
    }
}

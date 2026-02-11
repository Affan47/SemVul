vertice_reversed_get_or_build (long id)
{
    if (id <= 0 || id >= MAX_VERTICES)
        return NULL;

    int index = id - 1;
    Vertex * vertex = vertices_reversed[index];
    if (vertex == NULL) {
        vertex = vertex_new (id);
        vertices_reversed[index] = vertex;
    }
    return vertex;
}

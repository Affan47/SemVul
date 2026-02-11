vertice_original_get_or_build (long id)
{
    if (id <= 0 || id >= MAX_VERTICES)
        return NULL;

    int index = id - 1;
    Vertex * vertex = vertices_original[index];
    if (vertex == NULL) {
        vertex = vertex_new (id);
        vertices_original[index] = vertex;
        if (last_index < index)
            last_index = index;
        num_vertices++;
    }
    return vertex;
}

recompute_key (Vertex * tail, Vertex * head, int distance, void * user_data)
{
    if (vertex_explored (head)) return;

    Heap * heap = (Heap*) user_data;
    heap_remove (heap, head);

    long key = vertex_key (head);
    long dijkstra_score = shortest_distances[vertex_id(tail)] + distance;

    vertex_set_key (head, key < dijkstra_score ? key : dijkstra_score);

    heap_push (heap, head);
}

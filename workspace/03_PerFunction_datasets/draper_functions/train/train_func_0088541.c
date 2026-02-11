re_do_compile_fastmap(buffer, used, pos, can_be_null, fastmap)
    char *buffer, *fastmap, *can_be_null;
    int used, pos;
{
    char small_visited[512], *visited;

    if (used <= sizeof(small_visited))
	visited = small_visited;
    else {
	visited = malloc(used);
	if (!visited)
	    return 0;
    }
    *can_be_null = 0;
    memset(fastmap, 0, 256);
    memset(visited, 0, used);
    re_compile_fastmap_aux(buffer, pos, visited, can_be_null, fastmap);
    if (visited != small_visited)
	free(visited);
    return 1;
}

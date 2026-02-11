connected_components(signed char graph[MAX_CUTS][MAX_CUTS], int graph_size,
		     signed char component[MAX_CUTS])
{
  int num_components = 0;
  int k, j;

  if (graph_size <= 0)
    return 0;

  memset(component, -1, MAX_CUTS);
  for (;;) {
    int found_one;

    for (k = 0; k < graph_size; k++)
      if (component[k] == -1)
	break;
    if (k == graph_size)
      break;
    component[k] = num_components;
    do {
      found_one = 0;
      for (j = k+1; j < graph_size; j++)
	if (graph[k][j] && component[j] == -1) {
	  component[j] = num_components;
	  found_one = 1;
	}
    } while (found_one);
    num_components++;
  }
  gg_assert(num_components > 0);
  return num_components;
}

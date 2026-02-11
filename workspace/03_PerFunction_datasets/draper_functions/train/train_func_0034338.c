has_cycle(vector<int> &circuit_stack, AdjacencyList_t &g)
  {

    color_t color;
    graph_traits<AdjacencyList_t>::vertex_iterator vi, vi_end;
    for (tie(vi, vi_end) = vertices(g); vi != vi_end; ++vi)
      color[*vi] = white_color;


    for (tie(vi, vi_end) = vertices(g); vi != vi_end; ++vi)
      if (color[*vi] == white_color && has_cycle_dfs(g, *vi, color, circuit_stack))
        return true;

    return false;
  }

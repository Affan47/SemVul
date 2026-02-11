stl_write_edge(stl_file *stl, char *label, stl_hash_edge edge) {
  if (stl->error) return;
  printf("edge (%d)/(%d) %s\n", edge.facet_number, edge.which_edge, label);
  if(edge.which_edge < 3) {
    stl_write_vertex(stl, edge.facet_number, edge.which_edge % 3);
    stl_write_vertex(stl, edge.facet_number, (edge.which_edge + 1) % 3);
  } else {
    stl_write_vertex(stl, edge.facet_number, (edge.which_edge + 1) % 3);
    stl_write_vertex(stl, edge.facet_number, edge.which_edge % 3);
  }
}

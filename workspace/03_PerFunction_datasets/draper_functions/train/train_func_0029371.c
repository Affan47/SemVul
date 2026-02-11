stl_invalidate_shared_vertices(stl_file *stl) {
  if (stl->error) return;

  if (stl->v_indices != NULL) {
    free(stl->v_indices);
    stl->v_indices = NULL;
  }
  if (stl->v_shared != NULL) {
    free(stl->v_shared);
    stl->v_shared = NULL;
  }
}

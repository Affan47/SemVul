stl_write_obj (stl_file *stl, char *file) {
  int i;
  FILE* fp;

  if (stl->error) return;


  fp = fopen(file, "w");
  if (fp == NULL) {
    char* error_msg = (char*)malloc(81 + strlen(file));
    sprintf(error_msg, "stl_write_ascii: Couldn't open %s for writing", file);
    perror(error_msg);
    free(error_msg);
    stl->error = 1;
    return;
  }

  for (i = 0; i < stl->stats.shared_vertices; i++) {
    fprintf(fp, "v %f %f %f\n", stl->v_shared[i].x, stl->v_shared[i].y, stl->v_shared[i].z);
  }
  for (i = 0; i < stl->stats.number_of_facets; i++) {
    fprintf(fp, "f %d %d %d\n", stl->v_indices[i].vertex[0]+1, stl->v_indices[i].vertex[1]+1, stl->v_indices[i].vertex[2]+1);
  }

  fclose(fp);
}

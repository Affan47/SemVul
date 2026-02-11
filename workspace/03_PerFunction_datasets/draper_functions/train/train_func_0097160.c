load_point_cloud(FILE *in_stream, point_cloud *pc) {
  cloud_size_t size = 0;
  fscanf(in_stream, CLOUD_SIZE_FMT, &size);

  init_point_cloud(pc, size, size);

  for (cloud_size_t k = 0; k < pc->size; k++) {
    point pt;
    fscanf(in_stream, POINT_FMT, &pt.x, &pt.y);
    pc->points[k] = pt;
  }
}

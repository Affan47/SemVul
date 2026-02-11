save_point_cloud(point_cloud *pc, FILE *out_stream) {
  fprintf(out_stream, CLOUD_SIZE_FMT, pc->size);

  for (cloud_size_t k = 0; k < pc->size; k++) {
    fprintf(out_stream, POINT_FMT, pc->points[k].x, pc->points[k].y);
  }


  fprintf(out_stream, POINT_FMT, pc->points[0].x, pc->points[0].y);
}

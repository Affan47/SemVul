NumMoveSize(size_t size) {
  if (size == 0) return 0;

  int num = static_cast<int>(64.0 * 1024.0 / size);
  if (num < 2) num = 2;


  if (num > FLAGS_tcmalloc_transfer_num_objects)
    num = FLAGS_tcmalloc_transfer_num_objects;

  return num;
}

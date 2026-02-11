bp__init(bp_db_t* tree) {
  int ret;


  ret = bp__writer_find((bp__writer_t*) tree,
                        kNotCompressed,
                        BP__HEAD_SIZE,
                        &tree->head,
                        bp__tree_read_head,
                        bp__tree_write_head);
  if (ret == BP_OK) {

    bp_set_compare_cb(tree, bp__default_compare_cb);
  }

  return ret;
}

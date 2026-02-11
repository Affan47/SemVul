save_db(const char *fn, struct res_db *db)
{
  FILE *fp = fopen(fn, "w");
  struct conv_res *cr;
  if (!fp) {
    printf("failed to open (%s) to write\n", fn);
    return ;
  }
  for (cr = db->res_list.next; cr; cr = cr->next) {
    dump_res(fp, cr);
  }
}

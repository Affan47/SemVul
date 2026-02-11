inode_sort(void *n1, void *n2)
{
  ls_file_t *f1 = *((ls_file_t **) n1);
  ls_file_t *f2 = *((ls_file_t **) n2);
  int retval;

  return((retval = (f1->dir - f2->dir)) ? retval :
         ((retval = (f1->type - f2->type)) ? retval :
          (f1->inode_num - f2->inode_num)));
}

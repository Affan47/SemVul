populate_unmatched(struct fnode *x, struct fnode **array, int *index)
{
  struct fnode *a;
  for (a = x->next; a != x; a = a->next) {
    if (a->is_dir) {
      populate_unmatched(dir_children(a), array, index);
    } else {
      if (!a->x.file.content_peer && a->x.file.md5_defined) {
        array[*index] = a;
        ++*index;
      }
    }
  }
}

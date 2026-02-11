fs_retrieve(struct term *t,
			 struct context *subst,
			 struct is_tree *is,
			 struct fsub_pos **fs_pos)
{
  struct term_ptr *tp;
  struct is_pos *i_pos;
  struct fsub_pos *f_pos;

  if (t != NULL) {
    tp = is_retrieve(t, subst, is, &i_pos);
    if (tp == NULL)
      return(NULL);
    else {
      f_pos = get_fsub_pos();
      f_pos->pos = i_pos;
      f_pos->terms = tp;
      *fs_pos = f_pos;
      return(tp->term);
    }
  }
  else {
    f_pos = *fs_pos;
    tp = f_pos->terms->next;
    if (tp != NULL) {
      f_pos->terms = tp;
      return(tp->term);
    }
    else {
      tp = is_retrieve((struct term *) NULL, subst, is, &(f_pos->pos));
      if (tp == NULL) {
	free_fsub_pos(f_pos);
	return(NULL);
      }
      else {
	f_pos->terms = tp;
	return(tp->term);
      }
    }
  }
}

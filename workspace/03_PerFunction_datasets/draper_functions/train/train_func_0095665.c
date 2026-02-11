fpa_insert(struct term *t,
		int level,
		struct fpa_index *index)
{
  static int atom_count, term_count;

  int path[MAX_PATH];


  if (t->fpa_id == 0) {
    if (t->type != VARIABLE && t->varnum != 0)
      t->fpa_id = ++atom_count;
    else
      t->fpa_id = ++term_count;
  }
  term_fpa_rec(1, t, t, index, path, 0, level);
}

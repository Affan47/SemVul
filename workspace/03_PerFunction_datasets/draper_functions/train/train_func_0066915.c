ia_eval_dir_lemming (a_square_index pos)
{
  int mindist;
  a_square_index idx;
  int tmp, tmp2;
  a_lemming *tmppti;

  ia_cur_depth--;
  if (ia_cur_depth != 0) {
    square_occupied[pos] = 128;
    mindist = 0;
    tmppti = square_lemmings_list[pos];
    if (tmppti >= lemmings_support
	&& tmppti < (lemmings_support + lemmings_total)) {
      if (tmppti->couleur == ia_player)
	tmp2 = -100;
      else
	tmp2 = 20;
    } else
      tmp2 = 0;

    ia_eval_dir_lemming_inline (D_UP);
    ia_eval_dir_lemming_inline (D_RIGHT);
    ia_eval_dir_lemming_inline (D_DOWN);
    ia_eval_dir_lemming_inline (D_LEFT);

    mindist += tmp2;

    square_occupied[pos] = 0xff;
    ia_cur_depth++;
    return mindist;
  } else {
    ia_cur_depth++;
    tmp = ia_eval_neighb_pos (D_UP, pos) + ia_eval_neighb_pos (D_RIGHT, pos)
      + ia_eval_neighb_pos (D_DOWN, pos) + ia_eval_neighb_pos (D_LEFT, pos);
    return -(tmp << 2);
  }

}

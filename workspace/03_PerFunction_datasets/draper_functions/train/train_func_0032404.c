free_handicap_callback(int anchor, int color, struct pattern *pattern,
		       int ll, void *data)
{
  int r = -1;
  int k;
  int number_of_stones = 1;


  int move = AFFINE_TRANSFORM(pattern->move_offset, ll, anchor);

  UNUSED(data);


  for (k = 0; k < pattern->patlen; k++) {
    if (pattern->patn[k].att == ATT_not)
      number_of_stones++;
  }
  if (number_of_stones > remaining_handicap_stones)
    return;


  if (pattern->autohelper_flag & HAVE_CONSTRAINT) {
    if (!pattern->autohelper(ll, move, color, 0))
      return;
  }

  if (number_of_matches < MAX_HANDICAP_MATCHES) {
    r = number_of_matches;
    number_of_matches++;
  }
  else {
    int least_value = handicap_matches[0].value + 1;
    for (k = 0; k < number_of_matches; k++) {
      if (handicap_matches[k].value < least_value) {
	r = k;
	least_value = handicap_matches[k].value;
      }
    }
  }
  gg_assert(r >= 0 && r < MAX_HANDICAP_MATCHES);
  handicap_matches[r].value   = pattern->value;
  handicap_matches[r].anchor  = anchor;
  handicap_matches[r].pattern = pattern;
  handicap_matches[r].ll      = ll;
}

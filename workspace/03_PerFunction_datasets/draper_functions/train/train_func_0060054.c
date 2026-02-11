show_minimal_elidables(int tok_idx, int *later_indices, int next_index, int prev_can_shift_at, int *patcount)
{
  int can_shift_at;

  for (can_shift_at = tok_idx - 1;
       can_shift_at >= 0;
       can_shift_at--) {

    if (is_set(tok_idx, can_shift_at)) {
      break;
    }
  }

  if (can_shift_at < 0) {


    if (next_index < tokbuf.n - 1) {


      int i;
      if (*patcount == 1) {
        show_banner_for_minimal_paterns();
      }
      printf ("  Pattern %d : ", *patcount);
      ++*patcount;
      for (i=next_index-1; i>=0; i--) {
        TreeNode *tok = tokbuf.buf[later_indices[i]].yylval;
        printf (" %s", cmavo_table[tok->data.cmavo.code].cmavo);
      }
      printf("\n");
    }
  } else {


    int i;
    for (i=can_shift_at; i < tok_idx; i++) {


      if (i >= prev_can_shift_at) break;
      later_indices[next_index] = i;


      show_minimal_elidables(i, later_indices, next_index + 1, can_shift_at, patcount);
    }
  }
}

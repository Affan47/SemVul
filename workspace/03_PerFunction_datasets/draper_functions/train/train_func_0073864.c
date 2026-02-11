handle_lohu(void)
{
  TreeNode *x, *y;
  TreeNode *start, *end, *term;

  for (x = toks.next;
       x != &toks;
       x = x->next) {

    if (x->type == N_CMAVO &&
        x->data.cmavo.selmao == LOhU) {
      y = start = x->next;
      do {
        if (y == &toks) {
          fprintf(stderr, "Unterminated LOhU .. LEhU construction\n");
          exit(1);
        }
        if (y->type == N_CMAVO &&
            y->data.cmavo.selmao == LEhU) {
          term = y;
          end = term->prev;
          break;
        }
        y = y->next;
      } while (1);

      x->type = N_LOhU;
      x->data.lohu.text = build_string_from_nodes(start, end);

      term->next->prev = x;
      x->next = term->next;


    }
  }
}

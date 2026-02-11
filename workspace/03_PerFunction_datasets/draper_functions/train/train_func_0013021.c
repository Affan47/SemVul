print_last_toks(void)
{
  TreeNode *x;
  int i;

  fprintf(stderr, "Misparsed token :\n");
  if (next_tok != &toks) {
    print_token_details(next_tok);
  } else {
    fprintf(stderr, "  <End of text>\n");
  }

  fprintf(stderr, "Latest successfully parsed tokens :\n");
  for (x = next_tok->prev, i = 0;
       i < 8 && x != &toks;
       i++, x = x->prev) {

    print_token_details(x);

  }

}

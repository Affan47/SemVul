handle_zei(void)
{
  TreeNode *x, *nt;
  int first = 1;
  char **components;
  int total_comp_length;

  for (x = toks.next;
       x != &toks;
       x = nt, first=0) {

    nt = x->next;

    if (is_zei(x)) {

      int count = 1;
      int i;
      TreeNode *y, *z, *left, *right;

      if (first) {
        fprintf(stderr, "Cannot have 'zei' at the start of the text\n");
        had_bad_tokens = 1;
        nt = x->next;
        continue;
      }

      z = x;

      do {
      y = z->next;
        if (y == &toks) {
          fprintf(stderr, "Cannot have 'zei' at the end of the text\n");
          had_bad_tokens = 1;
          nt = x->next;
          goto done_this_block;
        }
        count++;
        z = y->next;
      } while ((z != &toks) && is_zei(z));

      x->type = N_ZEI;
      x->data.zei.nchildren = count;
      x->data.zei.children = new_array(TreeNode *, count);
      components = new_array(char *, count);

      total_comp_length = 0;
      for (i = 0, y = x->prev;
           i < count;
           i++, y = y->next->next) {
        x->data.zei.children[i] = y;
        components[i] = build_string_from_node(y);
        total_comp_length += strlen(components[i]);
      }

      x->data.zei.sep_with_plus = new_array(char, total_comp_length + (count - 1) + 1);
      x->data.zei.sep_with_zei  = new_array(char, total_comp_length + (count - 1) * 5 + 1);

      x->data.zei.sep_with_plus[0] = 0;
      x->data.zei.sep_with_zei[0] = 0;
      for (i=0; i<count; i++) {
        if (i > 0) {
          strcat(x->data.zei.sep_with_plus, "+");
          strcat(x->data.zei.sep_with_zei, " zei ");
        }
        strcat(x->data.zei.sep_with_plus, components[i]);
        strcat(x->data.zei.sep_with_zei, components[i]);
        Free(components[i]);
      }
      Free(components);

      left = x->prev->prev;
      right = y->prev;


      right->prev = x;
      left->next = x;
      x->next = right;
      x->prev = left;
      nt = right;

    }

done_this_block:
      continue;
  }

}

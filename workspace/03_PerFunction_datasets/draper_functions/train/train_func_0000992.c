do_get_nth_value(struct trie_node *node, int n)
{
  struct record_val *v = get_nth_val_ent(node, n, 0);
  if (v && v->type == RT_VAL) {
    return v->u.val;
  }
  return 0;
}

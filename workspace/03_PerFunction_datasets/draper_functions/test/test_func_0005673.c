free_keymaps (void)
{
  rp_keymap *cur;
  struct list_head *tmp, *iter;

  list_for_each_safe_entry (cur, iter, tmp, &rp_keymaps, node)
    {
      list_del (&cur->node);
      keymap_free (cur);
    }
}

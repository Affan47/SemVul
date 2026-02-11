insert(TreeMap *bt, struct Node *node,void *ExtraArgs)
{
  size_t depth = 0;

  node->down[0] = NULL;
  node->down[1] = NULL;

  if (bt->root == NULL) {
      bt->root = node;
      node->up = NULL;
    }
  else {
      struct Node *p = bt->root;
      for (;;) {
          int cmp, dir;

    	  cmp = bt->compare(node->data, p->data, ExtraArgs);
          if (cmp == 0)
            return p;
          depth++;

          dir = cmp > 0;
          if (p->down[dir] == NULL)
            {
              p->down[dir] = node;
              node->up = p;
              break;
            }
          p = p->down[dir];
        }
    }

  bt->count++;
  if (bt->count > bt->max_size)
    bt->max_size = bt->count;
  if (depth > calculate_h_alpha (bt->count)) {


      struct Node *s = node;
      size_t size = 1;
      size_t i;

      for (i = 1; ; i++)
        if (i < depth) {
            size += 1 + count_nodes_in_subtree (sibling (s));
            s = s->up;
            if (i > calculate_h_alpha (size)) {
                rebalance_subtree (bt, s, size);
                break;
              }
          }
        else {
            rebalance_subtree (bt, bt->root, bt->count);
            bt->max_size = bt->count;
            break;
          }
    }
    bt->timestamp++;
  return NULL;
}

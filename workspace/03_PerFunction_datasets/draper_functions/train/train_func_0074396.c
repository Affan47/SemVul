avl_insert(Avl_node p, void *item,
		    Ordertype (*compare) (void *, void *))
{
  if (p == NULL) {
    Avl_node new = get_avl_node();
    new->item = item;
    new->size = 1;
    new->height = 1;
    new->left = NULL;
    new->right = NULL;
    return new;
  }
  else {
    Ordertype relation = (*compare)(item, p->item);
    switch (relation) {
    case LESS_THAN:    p->left  = avl_insert(p->left,  item, compare); break;
    case GREATER_THAN: p->right = avl_insert(p->right, item, compare); break;
    case SAME_AS: fatal_error("avl_insert, item already there"); break;
    default:      fatal_error("avl_insert, not comparable"); break;
    }

    p = avl_fix(p);
    return p;
  }
}

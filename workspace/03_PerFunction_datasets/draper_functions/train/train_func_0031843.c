hashdict_unset(HashDict *hd, const char *key) {
   Node *n = _node_lookup(hd, key);
   if (n->next) {
      _destroy_node(hd, n->next);
      n->next = n->next->next;
      return true;
   }
   return false;
}

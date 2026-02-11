Destroy(Object** location) {
  Counters::global_handles.Decrement();
  if (location == NULL) return;
  Node* node = Node::FromLocation(location);
  node->Destroy();

  node->set_next_free(first_free());
  set_first_free(node);
}

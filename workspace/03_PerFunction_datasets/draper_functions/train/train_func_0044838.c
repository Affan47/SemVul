q_node_block_push (q_node_block_t *self, q_node_t *node) {
  if (self->length < QMAX_BLOCK_NODES) {


    self->nodes[self->length++] = node;


    if (self->length > 1) {
      self->nodes[self->length -2]->next = node;
      node->prev = self->nodes[self->length -2];
    }

    return self->length;
  }

  return QE_OVERFLOW;
}

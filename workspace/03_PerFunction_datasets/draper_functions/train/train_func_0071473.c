renumber_nodes (NODE_T * p, int *n)
{
  for (; p != NO_NODE; FORWARD (p)) {
    NUMBER (p) = (*n)++;
    renumber_nodes (SUB (p), n);
  }
}

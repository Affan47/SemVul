print_cell(int idx, struct cell *c)
{
  if (!c) {
    printf("idx =%d(null cell):\n", idx);
    return ;
  }
  printf("idx=%d:", idx);
  switch (c->type) {
  case TT_SUPER:
    print_super_cell(c);
    break;
  case TT_ALLOCED:
    print_alloced_cell();
    break;
  case TT_NODE:
    print_node_cell(c);
    break;
  case TT_UNUSED:
    print_unused_cell(c);
    break;
  case TT_BODY:
    print_body_cell(c);
    break;
  case TT_TAIL:
    print_tail_cell(c);
    break;
  default:
    printf("unknown\n");
  }
}

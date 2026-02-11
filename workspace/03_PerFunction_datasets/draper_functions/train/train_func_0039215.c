tre_ast_new_literal(tre_mem_t mem, int code_min, int code_max, int position)
{
  tre_ast_node_t *node;
  tre_literal_t *lit;

  node = tre_ast_new_node(mem, LITERAL, sizeof(tre_literal_t));
  if (!node)
    return NULL;
  lit = (tre_literal_t*)node->obj;
  lit->code_min = code_min;
  lit->code_max = code_max;
  lit->position = position;

  return node;
}

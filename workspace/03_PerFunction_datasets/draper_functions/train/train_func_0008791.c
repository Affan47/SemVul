param_print_name (const void *n1, VISIT order, int level)
{
  char *s1 = (*((paramNode_t **) n1))->name;
  char *t1 = (*((paramNode_t **) n1))->type;
  switch (order)
    {
    case postorder:
    case leaf:
      fprintf (paramFile, "\t%s %s;\n", t1, s1);
      break;
    default:
      break;
    }
  return;
}

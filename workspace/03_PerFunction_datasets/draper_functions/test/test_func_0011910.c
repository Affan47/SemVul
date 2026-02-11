reduced_init_owl(struct local_owl_data **owl, int at_bottom_of_stack)
{
  if (at_bottom_of_stack)
    owl_stack_pointer = 0;
  else
    owl_stack_pointer++;

  check_owl_stack_size();
  *owl = owl_stack[owl_stack_pointer];
  VALGRIND_MAKE_WRITABLE(*owl, sizeof(struct local_owl_data));
}

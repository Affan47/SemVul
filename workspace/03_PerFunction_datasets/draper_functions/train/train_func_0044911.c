delete_stack_container(struct z_stack_container *stack_data)
{
  if (stack_data == NULL)
    return;

  if (stack_data->z_stack != NULL)
    free(stack_data->z_stack);
  free(stack_data);
}

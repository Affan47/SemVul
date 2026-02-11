push_ref(int index, _stack *stack)
{
  int ref = stack->pop();
  char field_name[64];
  char type[64];
  int ret;

  if (java_class->get_ref_name_type(field_name, type, sizeof(field_name), ref) != 0)
  {
    printf("Error retrieving field name %d\n", ref);
    return -1;
  }


  if (optimize) { ret = generator->set_ref_local(index, field_name); }
  else { ret = -1; }

  if (ret == -1)
  {
    ret = generator->push_ref(field_name);
    ret |= generator->pop_ref_local(index);
  }

  return ret;
}

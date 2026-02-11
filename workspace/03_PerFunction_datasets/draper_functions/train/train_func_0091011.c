remove_temporary_equivalences (vec<tree> *stack)
{
  while (stack->length () > 0)
    {
      tree prev_value, dest;

      dest = stack->pop ();


      if (dest == NULL)
	break;

      prev_value = stack->pop ();
      set_ssa_name_value (dest, prev_value);
    }
}

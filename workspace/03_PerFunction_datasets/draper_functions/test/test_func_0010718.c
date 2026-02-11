directive_pop (directiveE *directive,
	       bfd_boolean *negated,
	       const char **file,
	       unsigned int *line,
	       const void **datum)
{
  state_stackS *top = directive_state_stack;

  if (!directive_state_stack)
    {
      as_bad (_("unmatched end directive"));
      *directive = directive_none;
      return;
    }

  directive_state[directive_state_stack->directive] = top->old_state;
  *directive = top->directive;
  *negated = top->negated;
  *file = top->file;
  *line = top->line;
  *datum = top->datum;
  directive_state_stack = top->prev;
  free (top);
}

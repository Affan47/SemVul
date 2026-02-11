expr_unwind ()
{
  while (--expr_depth > 0)
    {
      if (expr_stack[expr_depth]->tokstr)
	free (expr_stack[expr_depth]->tokstr);

      if (expr_stack[expr_depth]->expression)
	free (expr_stack[expr_depth]->expression);

      free (expr_stack[expr_depth]);
    }
  free (expr_stack[expr_depth]);

  noeval = 0;
}

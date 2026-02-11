single_dom_exit (struct loop *loop)
{
  edge exit = single_exit (loop);

  if (!exit)
    return NULL;

  if (!just_once_each_iteration_p (loop, exit->src))
    return NULL;

  return exit;
}

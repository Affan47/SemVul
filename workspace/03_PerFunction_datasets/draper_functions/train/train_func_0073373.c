setenv_routes (struct env_set *es, const struct route_list *rl)
{
  int i;
  for (i = 0; i < rl->n; ++i)
    setenv_route (es, &rl->routes[i], i + 1);
}

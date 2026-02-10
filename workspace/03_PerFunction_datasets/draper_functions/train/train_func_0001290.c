CLG_Initialise(void)
{
  clear_subnet(&top_subnet4);
  clear_subnet(&top_subnet6);
  if (CNF_GetNoClientLog()) {
    active = 0;
  } else {
    active = 1;
  }

  nodes = NULL;
  max_nodes = 0;
  n_nodes = 0;

  alloced = 0;
  alloc_limit = CNF_GetClientLogLimit();
  alloc_limit_reached = 0;
}

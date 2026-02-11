count_circuits(void)
{
  circuit_t *circ;
  int nr=0;

  for (circ = _circuit_get_global_list(); circ; circ = circ->next)
    nr++;

  return nr;
}

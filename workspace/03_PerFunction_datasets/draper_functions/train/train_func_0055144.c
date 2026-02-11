save_box_state()
{
  boxlo[0] = domain->boxlo[0];
  boxlo[1] = domain->boxlo[1];
  boxlo[2] = domain->boxlo[2];

  for (int i = 0; i < 6; i++)
    h_inv[i] = domain->h_inv[i];
}

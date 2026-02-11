pre_neighbor()
{
  for (int i = 0; i < n_pre_neighbor; i++)
    fix[list_pre_neighbor[i]]->pre_neighbor();
}

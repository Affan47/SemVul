CreateReject(uint8_g *matrix)
{
  int view, target;

  for (view=0; view < num_sectors; view++)
  for (target=0; target < view; target++)
  {
    sector_t *view_sec = LookupSector(view);
    sector_t *targ_sec = LookupSector(target);

    int p1, p2;

    if (view_sec->rej_group == targ_sec->rej_group)
      continue;


    p1 = view * num_sectors + target;
    p2 = target * num_sectors + view;

    matrix[p1 >> 3] |= (1 << (p1 & 7));
    matrix[p2 >> 3] |= (1 << (p2 & 7));
  }
}

AddIntersection(intersection_t ** cut_list,
    vertex_t *vert, seg_t *part, boolean_g self_ref)
{
  intersection_t *cut;
  intersection_t *after;


  for (cut=(*cut_list); cut; cut=cut->next)
  {
    if (vert == cut->vertex)
      return;
  }


  cut = NewIntersection();

  cut->vertex = vert;
  cut->along_dist = UtilParallelDist(part, vert->x, vert->y);
  cut->self_ref = self_ref;

  cut->before = VertexCheckOpen(vert, -part->pdx, -part->pdy);
  cut->after  = VertexCheckOpen(vert,  part->pdx,  part->pdy);


  for (after=(*cut_list); after && after->next; after=after->next)
  { }

  while (after && cut->along_dist < after->along_dist)
    after = after->prev;


  cut->next = after ? after->next : (*cut_list);
  cut->prev = after;

  if (after)
  {
    if (after->next)
      after->next->prev = cut;

    after->next = cut;
  }
  else
  {
    if (*cut_list)
      (*cut_list)->prev = cut;

    (*cut_list) = cut;
  }
}

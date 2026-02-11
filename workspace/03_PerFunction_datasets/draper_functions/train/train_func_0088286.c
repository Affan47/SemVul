remove_short_edges(ntuple_ll se, ntuple_list ls, double threshold)
{
  unsigned int i;
  double length;


  for(i=0; i<se->size; i++)
    {
      length = dist( ls->values[i*ls->dim + 0], ls->values[i*ls->dim + 1],
                     ls->values[i*ls->dim + 2], ls->values[i*ls->dim + 3] );

      if( length < threshold )
        {
          free_ntuple_list(se->list[i]);
          se->list[i] = NULL;
        }
    }


  for(i=0; i<se->size; i++)
    if( se->list[i] == NULL )
      {
        se->list[i] = se->list[se->size-1];
        se->size--;
        i--;
      }
}

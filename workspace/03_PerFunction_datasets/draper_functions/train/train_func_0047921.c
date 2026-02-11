removeBodyElementLoop(int bel_id)
{
  BodyElementLoop* bel = getBodyElementLoopById(bel_id);

  if ( bel == NULL )
    return modelStatistics->nofElementLoops;

  removeModelObject(bel->Id());

  return --modelStatistics->nofElementLoops;
}

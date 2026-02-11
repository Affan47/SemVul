closeMesh()
{
  int i;
  char filename[PATH_MAX];

  for(i = 0; i < meshFiles; ++i)
    {
      manager->closeStream(meshFileStream[i]);
    }

  if (clist) delete []clist;
  clist = (cache_node *)NULL;

  delete []elementTypeTags;
  delete []elementTypeCount;

  return 0;
}

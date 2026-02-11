read_sharedNode(int& tag,
		int& constraint,
		double *coord,
		int& partcount,
		int *parts)
{
  int i;
  fstream& str = meshFileStream[SHARED];

  if(step == sharedNodeCount)
    {
      rewind_stream(str);
      step = 0;
      return -1;
    }
  else if(step == 0)
    {
      cache_nodes();
    }

  str >> tag >> partcount;
  for(i = 0; i < partcount; ++i) str >> parts[i];

  cache_node *retval = search_node(tag);
  if(retval == NULL)
    {
      std::cout << "Partition error: PANIC PANIC!!! "<< tag << std::endl;
      exit(23);
    }
  else
    {
      constraint = retval->constraint;
      coord[0] = retval->x;
      coord[1] = retval->y;
      coord[2] = retval->z;
    }
  ++step;
  return 0;
}

group_is_null(group_type **treeN, long index)
{


  long i;

  for ( i = 0 ; i < setsz ; i++ )
    if (treeN[i][index] != (group_type) 0)
      return false;


  return true;
}

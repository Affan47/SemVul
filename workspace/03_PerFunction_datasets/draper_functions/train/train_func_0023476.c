setParentId(short parent_nbr, int parent_id)
{
  if ( modelData == NULL )
    return;

  if ( parent_nbr == 1 ) {
    modelData->parent1Id = parent_id;
  } else  {
    modelData->parent2Id = parent_id;
  }
}

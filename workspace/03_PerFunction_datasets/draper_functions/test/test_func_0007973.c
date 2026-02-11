isBemBoundary()
{
  int bd_id = getParentId(1);

  Body* bd = model->getBodyById(bd_id);

  if ( bd != NULL && BEM_BODY == bd->getType() )
    return true;
  else
    return false;
}

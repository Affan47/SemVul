getSubElement(int index)
{
  if ( modelData == NULL || modelData->nofSubElements == 0 )
    return NULL;

  if ( index < 0 || index >= modelData->nofSubElements )
    return NULL;

  return model->getVertexById((*modelData->subElementIds)[index]);
}

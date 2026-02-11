getElement(int index)
{
  if ( index < 0 || index >= nofElements ) return NULL;

  int be_id = elementIds[index];

  return model->getBodyElementById(be_id);
}

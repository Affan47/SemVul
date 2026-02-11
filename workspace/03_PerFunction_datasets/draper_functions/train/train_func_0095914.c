getMeshCornerElement(int index)
{
  if ( index < 0 ) return NULL;

  MeshCornerElementList::iterator pos = modelData->meshCornerElements->begin();
  MeshCornerElementList::iterator end_pos = modelData->meshCornerElements->end();

  for (int i = 0; i < index && pos != end_pos; i++,pos++);

  if ( pos == end_pos ) {
    return NULL;
  } else {
    return *pos;
  }
}

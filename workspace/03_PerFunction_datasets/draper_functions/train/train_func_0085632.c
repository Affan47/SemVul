ReadVertices (CObject *object, Chunk *previousChunk)
{
  int i;
  previousChunk->bytesRead += file->readUInt16 ((Uint16 *) &object->numVertices);

  object->vertex = new CVertex [object->numVertices];
  if (object->vertex == NULL) error_outofmemory ();
  memset (object->vertex, 0, sizeof (CVertex) * object->numVertices);

  CVector3 *p = new CVector3 [object->numVertices];
  if (p == NULL) error_outofmemory ();

  previousChunk->bytesRead += file->readFloat ((float *) p, (previousChunk->length - previousChunk->bytesRead) / 4);

  for (i = 0; i < object->numVertices; i ++)
  {
    object->vertex [i].vector.take (&p [i]);
  }


  for (i = 0; i < object->numVertices; i ++)
  {
    float fTempY = object->vertex [i].vector.y;
    object->vertex [i].vector.y = object->vertex [i].vector.z;
    object->vertex [i].vector.z = -fTempY;
  }
  delete p;
}

generate(const SbBox3f & bbox,
                                   const SbVec3f * vertices,
                                   const int numvertices)
{


  float sizes[3];
  float minvalues[3];
  int   offsets[3];

  bbox.getSize(sizes[0], sizes[1], sizes[2]);
  minvalues[0] = bbox.getMin()[0];
  minvalues[1] = bbox.getMin()[1];
  minvalues[2] = bbox.getMin()[2];
  offsets[0] = 0;
  offsets[1] = 1;
  offsets[2] = 2;


  if (sizes[0] < sizes[1]) {
    SbSwap(sizes[0], sizes[1]);
    SbSwap(minvalues[0], minvalues[1]);
    SbSwap(offsets[0], offsets[1]);
  }
  if (sizes[1] < sizes[2]) {
    SbSwap(sizes[1], sizes[2]);
    SbSwap(minvalues[1], minvalues[2]);
    SbSwap(offsets[1], offsets[2]);
  }
  if (sizes[0] < sizes[1]) {
    SbSwap(sizes[0], sizes[1]);
    SbSwap(minvalues[0], minvalues[1]);
    SbSwap(offsets[0], offsets[1]);
  }

  float s, t;
  for (int i = 0; i < numvertices; i++) {
    s = vertices[i][offsets[0]];
    t = vertices[i][offsets[1]];
    s -= minvalues[0];
    t -= minvalues[1];
    s /= sizes[0];
    t /= sizes[1];

    if (i >= PRIVATE(this)->texCoords.getLength()) PRIVATE(this)->texCoords.append(SbVec2f());
    PRIVATE(this)->texCoords[i].setValue(s, t);
  }


  PRIVATE(this)->texCoords.truncate(numvertices);
}

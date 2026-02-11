calcNormalDistance(int index)
{
  if ( normalDistances == NULL ||
       centers == NULL          ||
       normals == NULL
     )
    return;

  normalDistances[index] = dot3(normals[index], centers[index]);
}

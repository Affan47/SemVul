findRegion(vtkKdNode *node, double x, double y, double z)
{
  int regionId;

  if (!node->ContainsPoint(x, y, z, 0))
    {
    return -1;
    }

  if (node->GetLeft() == NULL)
    {
    regionId = node->GetID();
    }
  else
    {
    regionId = vtkKdTree::findRegion(node->GetLeft(), x, y, z);

    if (regionId < 0)
      {
      regionId = vtkKdTree::findRegion(node->GetRight(), x, y, z);
      }
    }

  return regionId;
}

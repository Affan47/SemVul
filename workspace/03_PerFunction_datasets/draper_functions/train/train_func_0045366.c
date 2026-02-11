GetRegionsAtLevel(int level, vtkKdNode **nodes)
{
  if ( (level < 0) || (level > this->Level))
    {
    return;
    }

  vtkKdTree::_GetRegionsAtLevel(level, nodes, this->Top);

  return;
}

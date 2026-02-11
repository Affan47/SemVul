GetLeafNodeCellInformation()
{
  if (!this->mRoot)
    {
    return NULL;
    }
  this->BuildLocatorIfNeeded();

  vtkIdListCollection *LeafCellsList = vtkIdListCollection::New();
  nodestack ns;
  BSPNode   *node = NULL;
  ns.push(this->mRoot);

  while (!ns.empty())
    {
    node = ns.top();
    ns.pop();
    if (node->mChild[0])
      {
      if (node->mChild[0])
        {
        ns.push(node->mChild[0]);
        }
      if (node->mChild[1])
        {
        ns.push(node->mChild[1]);
        }
      if (node->mChild[2])
        {
        ns.push(node->mChild[2]);
        }
      }
    else
      {
      vtkSmartPointer<vtkIdList> newList = vtkSmartPointer<vtkIdList>::New();
      LeafCellsList->AddItem(newList);
      newList->SetNumberOfIds(node->num_cells);
      for (int i=0; i<node->num_cells; i++)
        {
        newList->SetId(i, node->sorted_cell_lists[0][i]);
        }
      }
    }
  return LeafCellsList;
}

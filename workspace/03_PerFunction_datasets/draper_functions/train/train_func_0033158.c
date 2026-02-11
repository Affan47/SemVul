ZeroNumberOfPoints(vtkKdNode *kd)
{
  kd->SetNumberOfPoints(0);

  if (kd->GetLeft())
    {
    vtkKdTree::ZeroNumberOfPoints(kd->GetLeft());
    vtkKdTree::ZeroNumberOfPoints(kd->GetRight());
    }
}

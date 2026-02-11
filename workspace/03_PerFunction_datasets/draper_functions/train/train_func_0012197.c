AddNewRegions(vtkKdNode *kd, float *c1, int midpt, int dim, double coord)
{
  vtkKdNode *left = vtkKdNode::New();
  vtkKdNode *right = vtkKdNode::New();

  int npoints = kd->GetNumberOfPoints();

  int nleft = midpt;
  int nright = npoints - midpt;

  kd->AddChildNodes(left, right);

  double bounds[6];
  kd->GetBounds(bounds);

  left->SetBounds(
     bounds[0], ((dim == vtkKdTree::XDIM) ? coord : bounds[1]),
     bounds[2], ((dim == vtkKdTree::YDIM) ? coord : bounds[3]),
     bounds[4], ((dim == vtkKdTree::ZDIM) ? coord : bounds[5]));

  left->SetNumberOfPoints(nleft);

  right->SetBounds(
     ((dim == vtkKdTree::XDIM) ? coord : bounds[0]), bounds[1],
     ((dim == vtkKdTree::YDIM) ? coord : bounds[2]), bounds[3],
     ((dim == vtkKdTree::ZDIM) ? coord : bounds[4]), bounds[5]);

  right->SetNumberOfPoints(nright);

  left->SetDataBounds(c1);
  right->SetDataBounds(c1 + nleft*3);
}

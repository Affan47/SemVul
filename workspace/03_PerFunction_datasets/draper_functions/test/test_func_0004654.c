SelectCutDirection(vtkKdNode *kd)
{
  int dim=0, i;

  int xdir = 1 << vtkKdTree::XDIM;
  int ydir = 1 << vtkKdTree::YDIM;
  int zdir = 1 << vtkKdTree::ZDIM;


  if (this->ValidDirections == xdir)
    {
    dim = vtkKdTree::XDIM;
    }
  else if (this->ValidDirections == ydir)
    {
    dim = vtkKdTree::YDIM;
    }
  else if (this->ValidDirections == zdir)
    {
    dim = vtkKdTree::ZDIM;
    }
  else
    {


    double diff[3], dataBounds[6], maxdiff;
    kd->GetDataBounds(dataBounds);

    for (i=0; i<3; i++)
      {
      diff[i] = dataBounds[i*2+1] - dataBounds[i*2];
      }

    maxdiff = -1.0;

    if ((this->ValidDirections & xdir) && (diff[vtkKdTree::XDIM] > maxdiff))
      {
      dim = vtkKdTree::XDIM;
      maxdiff = diff[vtkKdTree::XDIM];
      }

    if ((this->ValidDirections & ydir) && (diff[vtkKdTree::YDIM] > maxdiff))
      {
      dim = vtkKdTree::YDIM;
      maxdiff = diff[vtkKdTree::YDIM];
      }

    if ((this->ValidDirections & zdir) && (diff[vtkKdTree::ZDIM] > maxdiff))
      {
      dim = vtkKdTree::ZDIM;
      }
    }
  return dim;
}

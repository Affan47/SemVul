AllocateOutputData(vtkImageData *output,
                                        int *uExtent)
{
  output->SetExtent(uExtent);


  vtkIdType numpts = 1;
  vtkIdType numcells = 1;
  for (int i = 0; i < 3; i++)
    {
    if (uExtent[i*2+1] >= uExtent[i*2])
      {
      vtkIdType dim = uExtent[i*2+1]-uExtent[i*2];
      numpts = numpts*(dim+1);
      if (dim != 0)
        {
        numcells = numcells*dim;
        }
      }
    }


  vtkImageData *in = vtkImageData::SafeDownCast(this->GetInputDataObject(0,0));

  vtkDataSetAttributes *ifd, *ofd;
  ifd = in->GetPointData();
  ofd = output->GetPointData();
  if (ifd && ofd)
    {
    ofd->CopyAllOn();
    ofd->CopyAllocate(ifd, numpts);
    ofd->SetNumberOfTuples(numpts);
    }
  ifd = in->GetCellData();
  ofd = output->GetCellData();
  if (ifd && ofd)
    {
    ofd->CopyAllOn();
    ofd->CopyAllocate(ifd, numcells);
    ofd->SetNumberOfTuples(numcells);
    }
}

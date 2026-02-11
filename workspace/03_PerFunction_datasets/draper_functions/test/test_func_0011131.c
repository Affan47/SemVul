CreateImageDataOutput(
  int partId, char line[80], const char* name,
  vtkMultiBlockDataSet *compositeOutput)
{
  char subLine[80];
  int lineRead;
  int iblanked = 0;
  int dimensions[3];
  float origin[3], delta[3];
  int numPts;

  this->NumberOfNewOutputs++;

  vtkDataSet* ds = this->GetDataSetFromBlock(compositeOutput, partId);
  if (ds == NULL || !ds->IsA("vtkImageData"))
    {
    vtkDebugMacro("creating new image data output");
    vtkImageData* idata = vtkImageData::New();
    this->AddToBlock(compositeOutput, partId, idata);
    idata->Delete();
    ds = idata;
    }

  vtkImageData* output = vtkImageData::SafeDownCast(ds);

  this->SetBlockName(compositeOutput, partId, name);

  if (sscanf(line, " %*s %*s %s", subLine) == 1)
    {
    if (strncmp(subLine, "iblanked", 8) == 0)
      {
      iblanked = 1;
      }
    }

  this->ReadIntArray(dimensions, 3);
  output->SetDimensions(dimensions);
  output->SetWholeExtent(
    0, dimensions[0]-1, 0, dimensions[1]-1, 0, dimensions[2]-1);
  this->ReadFloatArray(origin, 3);
  output->SetOrigin(origin[0], origin[1], origin[2]);
  this->ReadFloatArray(delta, 3);
  output->SetSpacing(delta[0], delta[1], delta[2]);

  if (iblanked)
    {
    vtkWarningMacro("VTK does not handle blanking for image data.");
    numPts = dimensions[0]*dimensions[1]*dimensions[2];
    if (dimensions[0] < 0 || dimensions[0]*this->SizeOfInt > this->FileSize ||
      dimensions[0] > this->FileSize ||
      dimensions[1] < 0 || dimensions[1]*this->SizeOfInt > this->FileSize ||
      dimensions[1] > this->FileSize ||
      dimensions[2] < 0 || dimensions[2]*this->SizeOfInt > this->FileSize ||
      dimensions[2] > this->FileSize ||
      numPts < 0 || numPts*this->SizeOfInt > this->FileSize ||
      numPts > this->FileSize)
      {
      return -1;
      }
    int *tempArray = new int[numPts];
    this->ReadIntArray(tempArray, numPts);
    delete [] tempArray;
    }


  lineRead = this->ReadLine(line);
  return lineRead;
}

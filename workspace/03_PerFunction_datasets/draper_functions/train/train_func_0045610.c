RequestData(vtkInformation*,
                                           vtkInformationVector** inputVector,
                                           vtkInformationVector*)
{
  vtkInformation* inInfo = inputVector[0]->GetInformationObject(0);

  this->InputInformation = inInfo;

  vtkCompositeDataSet *compositeData = vtkCompositeDataSet::SafeDownCast(
    inInfo->Get(vtkDataObject::DATA_OBJECT()));
  if (!compositeData)
    {
    vtkErrorMacro("No hierarchical input has been provided. Cannot write");
    this->InputInformation = 0;
    return 0;
    }


  this->CreateWriters(compositeData);

  this->SetErrorCode(vtkErrorCode::NoError);


  if(!this->Stream && !this->FileName)
    {
    vtkErrorMacro("Writer called with no FileName set.");
    this->SetErrorCode(vtkErrorCode::NoFileNameError);
    this->InputInformation = 0;
    return 0;
    }


  this->UpdateProgress(0);


  float wholeProgressRange[2] = {0,1};
  this->SetProgressRange(wholeProgressRange, 0, 1);


  this->SplitFileName();

  float progressRange[2] = {0,0};
  this->GetProgressRange(progressRange);


  std::string subdir = this->Internal->FilePath;
  subdir += this->Internal->FilePrefix;
  this->MakeDirectory(subdir.c_str());

  this->Internal->Root = vtkSmartPointer<vtkXMLDataElement>::New();
  this->Internal->Root->SetName(compositeData->GetClassName());

  int writerIdx=0;
  if (!this->WriteComposite(compositeData, this->Internal->Root, writerIdx))
    {
    this->RemoveWrittenFiles(subdir.c_str());
    return 0;
    }

  if (this->WriteMetaFile)
    {
    this->SetProgressRange(progressRange, this->GetNumberOfInputConnections(0),
                           this->GetNumberOfInputConnections(0)
                           + this->WriteMetaFile);
    int retVal = this->WriteMetaFileIfRequested();
    this->InputInformation = 0;
    return retVal;
    }


  this->UpdateProgressDiscrete(1);

  this->InputInformation = 0;
  return 1;
}

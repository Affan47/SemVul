WriteData()
{
  int type;
  vtkDataWriter *writer;
  vtkDataSet *input = vtkDataSet::SafeDownCast(this->GetInput());

  vtkDebugMacro(<<"Writing vtk dataset...");

  type = input->GetDataObjectType();
  if ( type == VTK_POLY_DATA )
    {
    vtkPolyDataWriter *pwriter = vtkPolyDataWriter::New();
    pwriter->SetInput(static_cast<vtkPolyData*>(input));
    writer = pwriter;
    }

  else if ( type == VTK_STRUCTURED_POINTS || type == VTK_IMAGE_DATA || type == VTK_UNIFORM_GRID)
    {
    vtkStructuredPointsWriter *spwriter = vtkStructuredPointsWriter::New();
    spwriter->SetInput(static_cast<vtkImageData*>(input));
    writer = spwriter;
    }

  else if ( type == VTK_STRUCTURED_GRID )
    {
    vtkStructuredGridWriter *sgwriter = vtkStructuredGridWriter::New();
    sgwriter->SetInput(static_cast<vtkStructuredGrid*>(input));
    writer = sgwriter;
    }

  else if ( type == VTK_UNSTRUCTURED_GRID )
    {
    vtkUnstructuredGridWriter *ugwriter = vtkUnstructuredGridWriter::New();
    ugwriter->SetInput(static_cast<vtkUnstructuredGrid*>(input));
    writer = ugwriter;
    }

  else if ( type == VTK_RECTILINEAR_GRID )
    {
    vtkRectilinearGridWriter *rgwriter = vtkRectilinearGridWriter::New();
    rgwriter->SetInput(static_cast<vtkRectilinearGrid*>(input));
    writer = rgwriter;
    }

  else
    {
    vtkErrorMacro(<< "Cannot write dataset type: " << type);
    return;
    }

  writer->SetFileName(this->FileName);
  writer->SetScalarsName(this->ScalarsName);
  writer->SetVectorsName(this->VectorsName);
  writer->SetNormalsName(this->NormalsName);
  writer->SetTensorsName(this->TensorsName);
  writer->SetTCoordsName(this->TCoordsName);
  writer->SetHeader(this->Header);
  writer->SetLookupTableName(this->LookupTableName);
  writer->SetFieldDataName(this->FieldDataName);
  writer->SetFileType(this->FileType);
  writer->SetDebug(this->Debug);
  writer->SetWriteToOutputString(this->WriteToOutputString);
  writer->Write();
  if (writer->GetErrorCode() == vtkErrorCode::OutOfDiskSpaceError)
    {
    this->SetErrorCode(vtkErrorCode::OutOfDiskSpaceError);
    }
  if (this->WriteToOutputString)
    {
    if (this->OutputString)
      {
      delete [] this->OutputString;
      }
    this->OutputStringLength = writer->GetOutputStringLength();
    this->OutputString = writer->RegisterAndGetOutputString();
    }
  writer->Delete();
}

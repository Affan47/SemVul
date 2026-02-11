WriteInternal()
{
  vtkDataSet* input = this->GetInput();
  vtkXMLPDataWriter* writer = 0;


  switch (input->GetDataObjectType())
    {
    case VTK_IMAGE_DATA:
    case VTK_STRUCTURED_POINTS:
      {
      vtkXMLPImageDataWriter* w = vtkXMLPImageDataWriter::New();
      w->SetInput(static_cast<vtkImageData*>(input));
      writer = w;
      } break;
    case VTK_STRUCTURED_GRID:
      {
      vtkXMLPStructuredGridWriter* w = vtkXMLPStructuredGridWriter::New();
      w->SetInput(static_cast<vtkStructuredGrid*>(input));
      writer = w;
      } break;
    case VTK_RECTILINEAR_GRID:
      {
      vtkXMLPRectilinearGridWriter* w = vtkXMLPRectilinearGridWriter::New();
      w->SetInput(static_cast<vtkRectilinearGrid*>(input));
      writer = w;
      } break;
    case VTK_UNSTRUCTURED_GRID:
      {
      vtkXMLPUnstructuredGridWriter* w = vtkXMLPUnstructuredGridWriter::New();
      w->SetInput(static_cast<vtkUnstructuredGrid*>(input));
      writer = w;
      } break;
    case VTK_POLY_DATA:
      {
      vtkXMLPPolyDataWriter* w = vtkXMLPPolyDataWriter::New();
      w->SetInput(static_cast<vtkPolyData*>(input));
      writer = w;
      } break;
    }


  if(!writer)
    {
    vtkErrorMacro("Cannot write dataset type: "
                  << input->GetDataObjectType());
    return 0;
    }


  writer->SetDebug(this->GetDebug());
  writer->SetFileName(this->GetFileName());
  writer->SetByteOrder(this->GetByteOrder());
  writer->SetCompressor(this->GetCompressor());
  writer->SetBlockSize(this->GetBlockSize());
  writer->SetDataMode(this->GetDataMode());
  writer->SetEncodeAppendedData(this->GetEncodeAppendedData());
  writer->SetNumberOfPieces(this->GetNumberOfPieces());
  writer->SetGhostLevel(this->GetGhostLevel());
  writer->SetStartPiece(this->GetStartPiece());
  writer->SetEndPiece(this->GetEndPiece());
  writer->AddObserver(vtkCommand::ProgressEvent, this->ProgressObserver);


  int writeSummary = 0;
  if(this->WriteSummaryFileInitialized)
    {
    writeSummary = this->WriteSummaryFile;
    }
  else if(this->StartPiece == 0)
    {
    writeSummary = 1;
    }
  writer->SetWriteSummaryFile(writeSummary);


  int result = writer->Write();


  writer->RemoveObserver(this->ProgressObserver);
  writer->Delete();
  return result;
}

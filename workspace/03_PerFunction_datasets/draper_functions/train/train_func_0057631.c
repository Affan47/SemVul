WriteInternal()
{
  vtkDataSet* input = vtkDataSet::SafeDownCast(this->GetInput());
  vtkXMLWriter* writer = 0;


  switch (input->GetDataObjectType())
    {
    case VTK_IMAGE_DATA:
    case VTK_STRUCTURED_POINTS:
      {
      vtkXMLImageDataWriter* w = vtkXMLImageDataWriter::New();
      w->SetInput(static_cast<vtkImageData*>(input));
      writer = w;
      } break;
    case VTK_STRUCTURED_GRID:
      {
      vtkXMLStructuredGridWriter* w = vtkXMLStructuredGridWriter::New();
      w->SetInput(static_cast<vtkStructuredGrid*>(input));
      writer = w;
      } break;
    case VTK_RECTILINEAR_GRID:
      {
      vtkXMLRectilinearGridWriter* w = vtkXMLRectilinearGridWriter::New();
      w->SetInput(static_cast<vtkRectilinearGrid*>(input));
      writer = w;
      } break;
    case VTK_UNSTRUCTURED_GRID:
      {
      vtkXMLUnstructuredGridWriter* w = vtkXMLUnstructuredGridWriter::New();
      w->SetInput(static_cast<vtkUnstructuredGrid*>(input));
      writer = w;
      } break;
    case VTK_POLY_DATA:
      {
      vtkXMLPolyDataWriter* w = vtkXMLPolyDataWriter::New();
      w->SetInput(static_cast<vtkPolyData*>(input));
      writer = w;
      } break;
    case VTK_HYPER_OCTREE:
      {
      vtkXMLHyperOctreeWriter* w = vtkXMLHyperOctreeWriter::New();
      w->SetInput(static_cast<vtkHyperOctree*>(input));
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
  writer->AddObserver(vtkCommand::ProgressEvent, this->ProgressObserver);


  int result = writer->Write();


  writer->RemoveObserver(this->ProgressObserver);
  writer->Delete();
  return result;
}

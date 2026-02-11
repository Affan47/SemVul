BuildSIL()
{

  this->SIL->Initialize();
  if (this->Parser)
    {


    this->SIL->ShallowCopy(this->Parser->GetSIL());
    return;
    }


  vtkSmartPointer<vtkVariantArray> childEdge =
    vtkSmartPointer<vtkVariantArray>::New();
  childEdge->InsertNextValue(0);

  vtkSmartPointer<vtkVariantArray> crossEdge =
    vtkSmartPointer<vtkVariantArray>::New();
  crossEdge->InsertNextValue(0);


  vtkUnsignedCharArray* crossEdgesArray = vtkUnsignedCharArray::New();
  crossEdgesArray->SetName("CrossEdges");
  this->SIL->GetEdgeData()->AddArray(crossEdgesArray);
  crossEdgesArray->Delete();

  std::deque<std::string> names;
  std::deque<vtkIdType> crossEdgeIds;
  int cc;


  vtkIdType rootId = this->SIL->AddVertex();
  names.push_back("SIL");


  vtkIdType blocksRoot = this->SIL->AddChild(rootId, childEdge);
  names.push_back("Blocks");


  this->SIL->AddChild(rootId, childEdge);
  names.push_back("Assemblies");


  this->SIL->AddChild(rootId, childEdge);
  names.push_back("Materials");


  std::map<std::string, vtkIdType> blockids;
  int numBlocks = this->GetNumberOfObjectsOfType(vtkExodusIIReader::ELEM_BLOCK);
  for (cc=0; cc < numBlocks; cc++)
    {
    vtkIdType child = this->SIL->AddChild(blocksRoot, childEdge);
    std::string block_name =
      this->GetObjectName(vtkExodusIIReader::ELEM_BLOCK, cc);
    names.push_back(block_name);
    blockids[block_name] = child;
    }


  vtkStringArray* namesArray = vtkStringArray::New();
  namesArray->SetName("Names");
  namesArray->SetNumberOfTuples(this->SIL->GetNumberOfVertices());
  this->SIL->GetVertexData()->AddArray(namesArray);
  namesArray->Delete();

  std::deque<std::string>::iterator iter;
  for (cc=0, iter = names.begin(); iter != names.end(); ++iter, ++cc)
    {
    namesArray->SetValue(cc, (*iter).c_str());
    }
}

ReadXMLData()
{


  this->Superclass::ReadXMLData();


  vtkXMLDataElement *ePrimary =
    this->XMLParser->GetRootElement()->GetNestedElement(0);

  int Dimension;
  double Size[3];
  double Origin[3];

  if (!ePrimary->GetScalarAttribute("Dimension", Dimension))
    {
    Dimension = 3;
    }

  if(ePrimary->GetVectorAttribute("Size", 3, Size) != 3)
    {
    Size[0] = 1;
    Size[1] = 1;
    Size[2] = 1;
    }

  if(ePrimary->GetVectorAttribute("Origin", 3, Origin) != 3)
    {
    Origin[0] = 0;
    Origin[1] = 0;
    Origin[2] = 0;
    }

  vtkHyperOctree *output = vtkHyperOctree::SafeDownCast(
      this->GetCurrentOutput());
  output->SetDimension(Dimension);
  output->SetSize(Size);
  output->SetOrigin(Origin);


  int numNested = ePrimary->GetNumberOfNestedElements();
  int i;
  for(i=0; i < numNested; ++i)
    {
    vtkXMLDataElement* eNested = ePrimary->GetNestedElement(i);
    if(strcmp(eNested->GetName(), "Topology") == 0)
      {
      this->ReadTopology(eNested);
      break;
      }
    }


  this->ReadPieceData();
}

WriteATextActor2D(vtkActor2D *anTextActor2D,
  vtkX3DExporterWriter* writer)
{
  char *ds;
  vtkTextActor *ta;
  vtkTextProperty *tp;

  if (!anTextActor2D->IsA("vtkTextActor"))
    {
    return;
    }

  ta = static_cast<vtkTextActor*>(anTextActor2D);
  tp = ta->GetTextProperty();
  ds = NULL;
  ds = ta->GetInput();

  if (ds==NULL)
    {
    return;
    }

  double temp[3];

  writer->StartNode(Transform);
  temp[0] = ((ta->GetPosition()[0])/(this->RenderWindow->GetSize()[0])) - 0.5;
  temp[1] = ((ta->GetPosition()[1])/(this->RenderWindow->GetSize()[1])) - 0.5;
  temp[2] = -2.0;
  writer->SetField(translation, SFVEC3F, temp);
  temp[0] = temp[1] = temp[2] = 0.002;
  writer->SetField(scale, SFVEC3F, temp);

  writer->StartNode(Shape);

  writer->StartNode(Appearance);

  writer->StartNode(Material);
  temp[0] = 0.0; temp[1] = 0.0; temp[2] = 1.0;
  writer->SetField(diffuseColor, SFCOLOR, temp);
  tp->GetColor(temp);
  writer->SetField(emissiveColor, SFCOLOR, temp);
  writer->EndNode();

  writer->EndNode();

  writer->StartNode(Text);
  writer->SetField(vtkX3D::string, ds);

  std::string familyStr;
  switch(tp->GetFontFamily())
    {
  case 0:
  default:
    familyStr = "\"SANS\"";
    break;
  case 1:
    familyStr = "\"TYPEWRITER\"";
    break;
  case 2:
    familyStr = "\"SERIF\"";
    break;
    }

  std::string justifyStr;
  switch  (tp->GetJustification())
    {
  case 0:
  default:
    justifyStr += "\"BEGIN\"";
    break;
  case 2:
    justifyStr += "\"END\"";
    break;
    }

  justifyStr += " \"BEGIN\"";

  writer->StartNode(FontStyle);
  writer->SetField(family, familyStr.c_str(), true);
  writer->SetField(topToBottom, tp->GetVerticalJustification() == 2);
  writer->SetField(justify, justifyStr.c_str(), true);
  writer->SetField(size, tp->GetFontSize());
  writer->EndNode();
  writer->EndNode();
  writer->EndNode();
  writer->EndNode();
}

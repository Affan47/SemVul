AreaPick(double x0, double y0, double x1, double y1,
                                    vtkRenderer *renderer)
{
  int picked = 0;
  vtkProp *propCandidate;
  vtkAbstractMapper3D *mapper = NULL;
  int pickable;


  this->Initialize();
  this->Renderer = renderer;

  this->SelectionPoint[0] = (x0+x1)*0.5;
  this->SelectionPoint[1] = (y0+y1)*0.5;
  this->SelectionPoint[2] = 0.0;


  this->InvokeEvent(vtkCommand::StartPickEvent,NULL);

  this->DefineFrustum(x0, y0, x1, y1, renderer);


  this->SetPath(renderer->PickProp(x0, y0, x1, y1));


  if ( this->Path )
    {
    picked = 1;


    propCandidate = this->Path->GetLastNode()->GetViewProp();


    pickable = this->TypeDecipher(propCandidate, &mapper);
    if ( pickable )
      {
      if ( mapper )
        {
        this->Mapper = mapper;
        vtkMapper *map1;
        vtkAbstractVolumeMapper *vmap;
        vtkImageMapper3D *imap;
        if ( (map1=vtkMapper::SafeDownCast(mapper)) != NULL )
          {
          this->DataSet = map1->GetInput();
          this->Mapper = map1;
          }
        else if ( (vmap=vtkAbstractVolumeMapper::SafeDownCast(mapper)) != NULL )
          {
          this->DataSet = vmap->GetDataSetInput();
          this->Mapper = vmap;
          }
        else if ( (imap=vtkImageMapper3D::SafeDownCast(mapper)) != NULL )
          {
          this->DataSet = imap->GetDataSetInput();
          this->Mapper = imap;
          }
        else
          {
          this->DataSet = NULL;
          }
        }
      }


    vtkPropCollection *pProps = renderer->GetPickResultProps();
    pProps->InitTraversal();

    vtkProp *prop;
    vtkAssemblyPath *path;
    while ((prop = pProps->GetNextProp()))
      {
      for ( prop->InitPathTraversal(); (path=prop->GetNextPath()); )
        {
        propCandidate = path->GetLastNode()->GetViewProp();
        pickable = this->TypeDecipher(propCandidate, &mapper);
        if ( pickable && !this->Prop3Ds->IsItemPresent(prop) )
          {
          this->Prop3Ds->AddItem(static_cast<vtkProp3D *>(prop));
          }
        }
      }


    this->Path->GetFirstNode()->GetViewProp()->Pick();
    this->InvokeEvent(vtkCommand::PickEvent,NULL);
    }

  this->InvokeEvent(vtkCommand::EndPickEvent,NULL);

  return picked;
}

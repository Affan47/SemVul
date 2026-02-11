Render(vtkRenderer *ren, vtkActor *act)
{


  if ( !this->GetInput() )
    {
    vtkErrorMacro(<< "No input!\n");
    return;
    }


  if ( this->LookupTable == NULL )
    {
    this->CreateDefaultLookupTable();
    }
  this->LookupTable->Build();


  if ( this->PolyDataMapper == NULL )
    {
    vtkDataSetSurfaceFilter *gf = vtkDataSetSurfaceFilter::New();
    vtkPolyDataMapper *pm = vtkPolyDataMapper::New();
    pm->SetInput(gf->GetOutput());

    this->GeometryExtractor = gf;
    this->PolyDataMapper = pm;
    }


  if (this->ClippingPlanes != this->PolyDataMapper->GetClippingPlanes())
    {
    this->PolyDataMapper->SetClippingPlanes(this->ClippingPlanes);
    }


  if ( this->GetInput()->GetDataObjectType() == VTK_POLY_DATA )
    {
    this->PolyDataMapper->SetInput(static_cast<vtkPolyData*>(this->GetInput()));
    }
  else
    {
    this->GeometryExtractor->SetInput(this->GetInput());
    this->PolyDataMapper->SetInput(this->GeometryExtractor->GetOutput());
    }


  this->PolyDataMapper->SetLookupTable(this->GetLookupTable());
  this->PolyDataMapper->SetScalarVisibility(this->GetScalarVisibility());
  this->PolyDataMapper->SetUseLookupTableScalarRange(
    this->GetUseLookupTableScalarRange());
  this->PolyDataMapper->SetScalarRange(this->GetScalarRange());
  this->PolyDataMapper->SetImmediateModeRendering(
    this->GetImmediateModeRendering());
  this->PolyDataMapper->SetColorMode(this->GetColorMode());
  this->PolyDataMapper->SetInterpolateScalarsBeforeMapping(
                               this->GetInterpolateScalarsBeforeMapping());

  this->PolyDataMapper->SetScalarMode(this->GetScalarMode());
  if ( this->ScalarMode == VTK_SCALAR_MODE_USE_POINT_FIELD_DATA ||
       this->ScalarMode == VTK_SCALAR_MODE_USE_CELL_FIELD_DATA )
    {
    if ( this->ArrayAccessMode == VTK_GET_ARRAY_BY_ID )
      {
      this->PolyDataMapper->ColorByArrayComponent(this->ArrayId,ArrayComponent);
      }
    else
      {
      this->PolyDataMapper->ColorByArrayComponent(this->ArrayName,ArrayComponent);
      }
    }

  this->PolyDataMapper->Render(ren,act);
  this->TimeToDraw = this->PolyDataMapper->GetTimeToDraw();
}

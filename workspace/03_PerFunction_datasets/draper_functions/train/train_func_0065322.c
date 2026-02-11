ProcessInformation(vtkInformation* info)
{
  if (info->Has(CLIPPING_PLANES()))
    {
    this->SetClippingPlanes(vtkPlaneCollection::SafeDownCast(
        info->Get(CLIPPING_PLANES())));
    }

  this->Superclass::ProcessInformation(info);
}

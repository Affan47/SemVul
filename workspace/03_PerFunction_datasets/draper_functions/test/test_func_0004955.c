GetNumberOfFaces()
{

  if ( ! this->FacesGenerated )
    {
    this->GenerateFaces();
    }

  if (this->GlobalFaces->GetNumberOfTuples() == 0)
    {
    return 0;
    }

  return static_cast<int>(this->GlobalFaces->GetValue(0));
}

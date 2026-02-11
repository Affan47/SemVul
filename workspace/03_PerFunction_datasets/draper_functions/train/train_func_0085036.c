GetNumberOfPlanes()
{
  if ( this->Points && this->Normals )
    {
    int npts = this->Points->GetNumberOfPoints();
    int nnormals = this->Normals->GetNumberOfTuples();
    return ( npts <= nnormals ? npts : nnormals );
    }
  else
    {
    return 0;
    }
}

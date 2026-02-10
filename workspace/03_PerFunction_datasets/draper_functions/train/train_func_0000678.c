GetCellId( int displayPos[2] )
{
  if (this->EnableVertexPicking)
    {
    return -1;
    }
  this->Update( displayPos );
  return this->CellId;
}

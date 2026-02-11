SetMaterialArrays( int M,  const char* volume, const char* normalX, const char* normalY, const char* normalZ, const char* ordering )
{
  this->NumberOfDomains = -1;
  if( M < 0 )
    {
    vtkErrorMacro(<<"Bad material index "<<M<<"\n");
    return;
    }
  else if( M >= this->GetNumberOfMaterials() )
    {
    this->SetNumberOfMaterials(M+1);
    }
  vtkDebugMacro(<<"Set Material "<<M<<" : "<<volume<<","<<normalX<<","<<normalY<<","<<normalZ<<","<<ordering<<"\n");
  vtkYoungsMaterialInterfaceInternals::MaterialDescription md;
  md.setVolume(volume);
  md.setNormal("");
  md.setNormalX(normalX);
  md.setNormalY(normalY);
  md.setNormalZ(normalZ);
  md.setOrdering(ordering);
  this->Internals->Materials[M] = md;
  this->Modified();
}

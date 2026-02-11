PrintSelf(ostream& os, vtkIndent indent)
{
  os << indent << "Target Texture Size: "
     << this->TargetTextureSize[0] << ", "
     << this->TargetTextureSize[1] << endl;

  os << indent << "Maximum Number Of Planes: ";
  if ( this->MaximumNumberOfPlanes > 0 )
    {
    os << this->MaximumNumberOfPlanes << endl;
    }
  else
    {
    os << "<unlimited>" << endl;
    }

  os << indent << "Maximum Storage Size: "
     << this->MaximumStorageSize << endl;

  this->Superclass::PrintSelf(os,indent);
}

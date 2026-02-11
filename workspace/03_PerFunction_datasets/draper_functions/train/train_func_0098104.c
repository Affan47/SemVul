PrintSelf(ostream& os, vtkIndent indent)
{
  this->Superclass::PrintSelf(os,indent);

  os << indent << "AttenuationValues: (" << this->AttenuationValues[0] << ", "
     << this->AttenuationValues[1] << ", "
     << this->AttenuationValues[2] << ")\n";
  os << indent << "AmbientColor: (" << this->AmbientColor[0] << ", "
     << this->AmbientColor[1] << ", " << this->AmbientColor[2] << ")\n";
  os << indent << "DiffuseColor: (" << this->DiffuseColor[0] << ", "
     << this->DiffuseColor[1] << ", " << this->DiffuseColor[2] << ")\n";
  os << indent << "SpecularColor: (" << this->SpecularColor[0] << ", "
     << this->SpecularColor[1] << ", " << this->SpecularColor[2] << ")\n";
  os << indent << "Cone Angle: " << this->ConeAngle << "\n";
  os << indent << "Exponent: " << this->Exponent << "\n";
  os << indent << "Focal Point: (" << this->FocalPoint[0] << ", "
     << this->FocalPoint[1] << ", " << this->FocalPoint[2] << ")\n";
  os << indent << "Intensity: " << this->Intensity << "\n";
  os << indent << "Position: (" << this->Position[0] << ", "
     << this->Position[1] << ", " << this->Position[2] << ")\n";
  os << indent << "Positional: " << (this->Positional ? "On\n" : "Off\n");
  os << indent << "Switch: " << (this->Switch ? "On\n" : "Off\n");

  os << indent << "LightType: ";
  if (this->LightType == VTK_LIGHT_TYPE_HEADLIGHT)
    {
    os << "Headlight\n";
    }
  else if (this->LightType == VTK_LIGHT_TYPE_CAMERA_LIGHT)
    {
    os << "CameraLight\n";
    }
  else if (this->LightType == VTK_LIGHT_TYPE_SCENE_LIGHT)
    {
    os << "SceneLight\n";
    }
  else
    {
    os << "(unknown light type)\n";
    }

  os << indent << "TransformMatrix: ";
  if(this->TransformMatrix != NULL)
    {
    os << this->TransformMatrix << "\n";
    }
  else
    {
    os << "(none)\n";
    }
}

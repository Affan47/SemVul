PrintSelf(ostream& os, vtkIndent indent)
{
  this->Superclass::PrintSelf(os, indent);
  int i;
  for (i = 0; i < this->OpacityArrayLength; i++)
    {
    os << indent << "Opacity(" << i << "): " << this->GetOpacity(i) << endl;
    }
  os << indent << "Stencil: " << this->GetStencil() << endl;
  os << indent << "BlendMode: " << this->GetBlendModeAsString() << endl
     << indent << "CompoundThreshold: " << this->CompoundThreshold << endl;
}

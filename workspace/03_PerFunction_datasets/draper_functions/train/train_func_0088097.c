GetMinimumColor(unsigned char rgba[4])
{
  VTK_LEGACY_REPLACED_BODY(vtkWindowLevelLookupTable::GetMinimumColor, "VTK 5.0",
                           vtkWindowLevelLookupTable::GetMinimumTableValue);
  rgba[0] = int(this->MinimumTableValue[0]*255);
  rgba[1] = int(this->MinimumTableValue[1]*255);
  rgba[2] = int(this->MinimumTableValue[2]*255);
  rgba[3] = int(this->MinimumTableValue[3]*255);
}

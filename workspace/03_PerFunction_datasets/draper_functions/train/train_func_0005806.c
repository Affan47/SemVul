SetField(int attributeID, int type, const double* d)
{
  *this->OutputStream << " " << x3dAttributeString[attributeID] << "=\"";
  switch (type)
    {
    case(SFVEC3F):
    case(SFCOLOR):
      *this->OutputStream << d[0]
                         << " "
                         << d[1]
                         << " "
                         << d[2];
      break;
    case(SFROTATION):
      *this->OutputStream << d[1]
                         << " "
                         << d[2]
                         << " "
                         << d[3]
                         << " "
                         << vtkMath::RadiansFromDegrees( -d[0] );
      break;
    default:
      *this->OutputStream << "UNKNOWN DATATYPE";
    }
  *this->OutputStream << "\"";
}

Print(std::ostream &os) const {
    os << "Group           0x" <<  std::hex << Group << std::dec << std::endl;
    os << "Dimensions                         :" << Dimensions << std::endl;
    os << "NumberOfPoints                     :" << NumberOfPoints << std::endl;
    os << "TypeOfData                         :" << TypeOfData << std::endl;
    os << "CurveDescription                   :" << CurveDescription << std::endl;
    os << "DataValueRepresentation            :" << DataValueRepresentation << std::endl;
    unsigned short * p = (unsigned short*)&Data[0];
    for(unsigned short i = 0; i < NumberOfPoints; i+=2)
      {
      os << p[i] << "," << p[i+1] << std::endl;
      }
  }

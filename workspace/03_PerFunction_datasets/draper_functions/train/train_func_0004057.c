string2ValueScale(
         std::string const& string)
{
  CSF_VS valueScale = VS_UNDEFINED;


  if(string == "VS_BOOLEAN") {
    valueScale = VS_BOOLEAN;
  }
  else if(string == "VS_NOMINAL") {
    valueScale = VS_NOMINAL;
  }
  else if(string == "VS_ORDINAL") {
    valueScale = VS_ORDINAL;
  }
  else if(string == "VS_SCALAR") {
    valueScale = VS_SCALAR;
  }
  else if(string == "VS_DIRECTION") {
    valueScale = VS_DIRECTION;
  }
  else if(string == "VS_LDD") {
    valueScale = VS_LDD;
  }

  else if(string == "VS_CLASSIFIED") {
    valueScale = VS_CLASSIFIED;
  }
  else if(string == "VS_CONTINUOUS") {
    valueScale = VS_CONTINUOUS;
  }
  else if(string == "VS_NOTDETERMINED") {
    valueScale = VS_NOTDETERMINED;
  }

  return valueScale;
}

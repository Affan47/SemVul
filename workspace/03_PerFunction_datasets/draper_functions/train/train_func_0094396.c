IsActive()
{
  ParameterField* pf = getFieldByGuiName("ACTIVE");


  if ( pf == NULL ) {
    return true;
  }

  char** data = pf->getDataStrings();

  if ( !LibFront::ncEqual((char*)data[0], "true") ) {
    return false;

  } else {
    return true;
  }
}

_makeInst_BaseBoard( const CMPIBroker * _broker,
	       const CMPIContext * ctx,
	       const CMPIObjectPath * ref,
	       const char ** properties,
	       CMPIStatus * rc) {
  CMPIObjectPath *  op            = NULL;
  CMPIInstance   *  ci            = NULL;
  struct cim_baseboard data;
  const char     ** keys          = NULL;
  char              keylist[1000] = "CreationClassName\0Tag\0";
  char           *  key           = keylist;
  int               i;

  _OSBASE_TRACE(2,("--- _makeInst_BaseBoard() called"));

  if(get_baseboard_data(&data)) {
    CMSetStatusWithChars( _broker, rc,
			  CMPI_RC_ERR_FAILED, "Could not get Base Board data." );
    _OSBASE_TRACE(2,("--- _makeInst_BaseBoard() failed : %s",CMGetCharPtr(rc->msg)));
    return ci;
  }

  op = CMNewObjectPath( _broker, CMGetCharPtr(CMGetNameSpace(ref,rc)),
			_ClassName, rc );
  if( CMIsNullObject(op) ) {
    CMSetStatusWithChars( _broker, rc,
			  CMPI_RC_ERR_FAILED, "Create CMPIObjectPath failed." );
    _OSBASE_TRACE(2,("--- _makeInst_BaseBoard() failed : %s",CMGetCharPtr(rc->msg)));
    return ci;
  }

  ci = CMNewInstance( _broker, op, rc);
  if( CMIsNullObject(ci) ) {
    CMSetStatusWithChars( _broker, rc,
			  CMPI_RC_ERR_FAILED, "Create CMPIInstance failed." );
    _OSBASE_TRACE(2,("--- _makeInst_BaseBoard() failed : %s",CMGetCharPtr(rc->msg)));
    return ci;
  }


  keys = calloc(3,sizeof(char*));
  for(i=0;i<2;i++) {
    keys[i] = key;
    key = key + strlen(key) + 1;
  }
  CMSetPropertyFilter(ci,properties,keys);
  free(keys);

  CMSetProperty( ci, "CreationClassName", _ClassName, CMPI_chars );
  CMSetProperty( ci, "Tag", data.tag, CMPI_chars );

  CMSetProperty( ci, "Manufacturer", data.vendor, CMPI_chars);
  CMSetProperty( ci, "Model", data.model, CMPI_chars);
  CMSetProperty( ci, "VendorEquipmentType", data.type, CMPI_chars);
  CMSetProperty( ci, "PartNumber", data.partNumber, CMPI_chars);
  CMSetProperty( ci, "SerialNumber", data.serialNumber, CMPI_chars);
  CMSetProperty( ci, "UUID", data.UUID, CMPI_chars);

  CMSetProperty( ci, "PoweredOn",(CMPIValue*)&CMPI_true, CMPI_boolean);
  CMSetProperty( ci, "HostingBoard",(CMPIValue*)&CMPI_true, CMPI_boolean);

  CMSetProperty( ci, "Caption", "Base Board", CMPI_chars);
  CMSetProperty( ci, "Description", "A class derived from Card to deliver the systems base board hardware information.", CMPI_chars);


#ifndef CIM26COMPAT
  CMSetProperty( ci, "ElementName", data.tag, CMPI_chars);
#endif

  free_baseboard_data(&data);
  _OSBASE_TRACE(2,("--- _makeInst_BaseBoard() exited"));
  return ci;
}

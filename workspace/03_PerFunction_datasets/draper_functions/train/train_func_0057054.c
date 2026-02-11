AddGeomTable(const char* datalayername, const char* geomname, OGRwkbGeometryType eType) {
  static char layername[512];
  layername[0] = '\0';
  strcat(layername, datalayername);
  strcat(layername, "_");
  strcat(layername, geomname);

  OGRILI1Layer* geomlayer = new OGRILI1Layer(layername, NULL, 0, eType, NULL);
  AddLayer(geomlayer);
  OGRFieldDefn fieldDef("_TID", OFTString);
  geomlayer->GetLayerDefn()->AddFieldDefn(&fieldDef);
  if (eType == wkbPolygon)
  {
     OGRFieldDefn fieldDefRef("_RefTID", OFTString);
     geomlayer->GetLayerDefn()->AddFieldDefn(&fieldDefRef);
  }
  OGRFieldDefn fieldDef2("ILI_Geometry", OFTString);
  geomlayer->GetLayerDefn()->AddFieldDefn(&fieldDef2);
  return geomlayer;
}

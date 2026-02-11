free_geom_conv(DataGeomConv GeomConv)
{
 gint i,j;

 for(i = 0;i<GeomConv.Ntype;i++)
		if(GeomConv.TypeData[i])
			g_free(GeomConv.TypeData[i]);

 if(GeomConv.GeomFile)
		g_free(GeomConv.GeomFile);
 GeomConv.GeomFile = NULL;
 if(GeomConv.TypeData)
		g_free(GeomConv.TypeData);
 GeomConv.TypeData = NULL;

 if(GeomConv.TypeCalcul)
		g_free(GeomConv.TypeCalcul);
 GeomConv.TypeCalcul = NULL;

  if( GeomConv.Npoint<1)
  {
	if(GeomConv.Data)
		g_free(GeomConv.Data);
        GeomConv.Data = NULL;
	if(GeomConv.NumGeom)
		g_free(GeomConv.NumGeom);
	GeomConv.NumGeom = NULL;
	return GeomConv;
  }
 for(j = 0;j<GeomConv.Ntype;j++)
 {
  	if(GeomConv.Data[j])
  	for(i = 0;i<GeomConv.Npoint;i++)
		if(GeomConv.Data[j][i])
			g_free(GeomConv.Data[j][i]);

  	if(GeomConv.Data[j])
		g_free(GeomConv.Data[j]);

  	GeomConv.Data[j] = NULL;
 }
 GeomConv.Npoint = 0;
 GeomConv.Ntype  = 0;

 return GeomConv;
}

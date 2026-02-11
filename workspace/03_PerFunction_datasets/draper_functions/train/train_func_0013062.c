bonded(gint i,gint j)
{
	GLdouble distance;
	V3d dif;
	gint k;

	for(k=0;k<3;k++)
		dif[k] = (GeomOrb[i].C[k] - GeomOrb[j].C[k]);

	distance = v3d_length(dif);

	if(distance<(GeomOrb[i].Prop.covalentRadii + GeomOrb[j].Prop.covalentRadii))
		return TRUE;
	else
		return FALSE;
}

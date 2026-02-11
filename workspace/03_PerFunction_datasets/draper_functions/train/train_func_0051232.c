get_geometry_type_from_psicode_input_file(gchar *NomFichier)
{
 gchar *t;
 FILE *fd;
 guint taille=BSIZE;
 FilePosTypeGeom j;


 j.geomtyp=GEOM_IS_OTHER;
 j.numline=0;
 j.units=1;

 t = g_malloc(taille*sizeof(gchar));
 fd = FOpen(NomFichier, "rb");
 if(fd==NULL) return j;
 while(!feof(fd) )
 {
 	if(!fgets(t, taille, fd)) break;
	g_strup(t);

	if(strstr(t,"MOLECULE"))
	{
		gint charge,mult;
		gboolean OK = FALSE;
		gint i;
		if(fgets(t,taille,fd) && 2==sscanf(t,"%d %d",&charge,&mult)) OK = TRUE;
		else OK = FALSE;

		if(OK && fgets(t,taille,fd))
		{
			gchar*t1 = g_malloc(taille*sizeof(gchar));
			gchar*t2 = g_malloc(taille*sizeof(gchar));
			gchar*t3 = g_malloc(taille*sizeof(gchar));
			gchar*t4 = g_malloc(taille*sizeof(gchar));

        		i = sscanf(t,"%s %s %s %s",t1,t2,t3,t4);
			if(i==4)j.geomtyp = GEOM_IS_XYZ;
			else j.geomtyp = GEOM_IS_ZMAT;
  			g_free(t1);
  			g_free(t2);
  			g_free(t3);
  			g_free(t4);
		}
		break;
	}
  	j.numline++;
  }
  fclose(fd);
  g_free(t);
  return j;
}

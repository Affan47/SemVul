get_num_orbitals_from_aux_mopac_file(FILE* file, gchar* blockName,  gint* begin, gint* end)
{
	gchar t[BBSIZE];
	*begin = 0;
	*end = 0;
	 while(!feof(file))
	 {
		if(!fgets(t,BBSIZE,file))break;
		if(strstr( t, blockName))
		{
			gchar* pdest = strstr( t, "=")+1;
			gint i = sscanf(pdest,"%d %d",begin,end);
			return i;
		}
	 }
	 return 0;
}

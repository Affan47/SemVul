save_HBonds_properties()
{
	gchar *hbondsfile;
	FILE *file;
	gint i;

	hbondsfile = g_strdup_printf("%s%shbonds",gabedit_directory(),G_DIR_SEPARATOR_S);

	file = FOpen(hbondsfile, "w");
	if(!file) return;

 	fprintf(file,"%f\n",minDistance);
 	fprintf(file,"%f\n",maxDistance);
 	fprintf(file,"%f\n",minAngle);
 	fprintf(file,"%f\n",maxAngle);
 	fprintf(file,"%d\n",nAtomsCanConnect);
	for(i=0;i<nAtomsCanConnect;i++) fprintf(file,"%s\n",atomsCanConnect[i]);
	fclose(file);

	g_free(hbondsfile);
}

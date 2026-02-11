saveAllPersonalFragments(PersonalFragments* personnalFragments,gchar* filename)
{
	FILE* file;
	file = FOpen(filename,"w");

	if(personnalFragments == NULL)
		return FALSE;
	if(file == NULL)
		return FALSE;
	else
	{
		saveTitlePesoFrag(file);
		saveGroupesList(personnalFragments,file);
		saveAllFragmentsList(personnalFragments,file);
		saveAllFragments(personnalFragments,file);
		fclose(file);
	}
	return TRUE;
}

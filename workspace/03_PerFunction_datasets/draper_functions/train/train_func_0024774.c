openFile (const char* pcAccess)
{
	closeFile ();
	file = fopen (strFilename.c_str(),pcAccess);
	if (!file)
		throwException ("Erreur lors de l'ouverture du fichier");
}

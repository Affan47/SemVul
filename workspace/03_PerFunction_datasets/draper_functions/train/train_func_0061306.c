AllocateGUIS_ (void)
{
static GUIS		*guiSP;


guiSP = (GUIS *) calloc (1, sizeof (GUIS));

if (guiSP == NULL)
	{
	ErrorMessage_ ("garlic", "AllocateGUIS_", "",
		"Failed to allocate memory for GUIS structure!\n",
		"", "", "");
	}


return guiSP;
}

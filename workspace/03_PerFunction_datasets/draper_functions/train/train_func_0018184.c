RemoveGPSTags(char* File, int NoChangeMtime)
{
	if (RemoveGPSExif(File, NoChangeMtime))
	{
		printf("%s: Removed GPS tags.\n", File);
	} else {
		printf("%s: Tag removal failure.\n", File);
	}
}

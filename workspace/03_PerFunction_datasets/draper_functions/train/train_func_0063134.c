readNext (tagFile *const file, tagEntry *const entry)
{
	tagResult result;
	if (file == NULL  ||  ! file->initialized)
		result = TagFailure;
	else if (! readTagLine (file))
		result = TagFailure;
	else
	{
		if (entry != NULL)
			parseTagLine (file, entry);
		result = TagSuccess;
	}
	return result;
}

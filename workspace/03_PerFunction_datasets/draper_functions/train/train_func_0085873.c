primaryFile()
{
	if (isGLE())
		return(gleFileName);
	else if (isEPS())
		return(epsFileName);
	else
		return QString();
}

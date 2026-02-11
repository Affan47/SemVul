CL_Mapname_m ( char *buffer, int bufferSize )
{
	if(cls.mapname[0])
		Q_strncpyz(buffer, cls.mapname, bufferSize);
	else
		Q_strncpyz(buffer, "nomap", bufferSize );
}

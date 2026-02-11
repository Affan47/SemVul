CL_LocHere_m( char *buffer, int bufferSize )
{
	const cl_location_t	*loc;

	if (!cl_locations || cls.state != ca_active) {
		Q_strncpyz ( buffer, "%L", bufferSize );
		return;
	}

	loc = CL_Loc_Get(cl.refdef.vieworg);
	Q_strncpyz(buffer, loc->name, bufferSize);

}

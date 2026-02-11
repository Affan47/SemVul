PF_Configstring (int index, char *val)
{
	if (index < 0 || index >= MAX_CONFIGSTRINGS)
		Com_Error (ERR_DROP, "configstring: bad index %i (data: %s)\n", index, val);

	if (!val)
		val = "";


	strcpy (sv.configstrings[index], val);


	if (sv.state != ss_loading)
	{
		SZ_Clear (&sv.multicast);
		MSG_WriteChar (&sv.multicast, svc_configstring);
		MSG_WriteShort (&sv.multicast, index);
		MSG_WriteString (&sv.multicast, val);

		SV_Multicast (vec3_origin, MULTICAST_ALL_R);
	}
}

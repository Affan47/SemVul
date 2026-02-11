ignore_attr_type(const char *attr_type)
{
	if ( !attr_type ||
		 (strcasecmp (attr_type, "cn") == 0) ||
		 (strcasecmp (attr_type, "aci") == 0) ||
		 (strcasecmp (attr_type, "objectclass") == 0) ||
		 (strcasecmp (attr_type, "numsubordinates") == 0) ||
		 (strcasecmp (attr_type, "internalModifiersname") == 0) ||
		 (strcasecmp (attr_type, "internalCreatorsname") == 0) ||
		 (strcasecmp (attr_type, "modifytimestamp") == 0) ||
		 (strcasecmp (attr_type, "modifiersname") == 0)) {
		return 1;
	}

	return 0;
}

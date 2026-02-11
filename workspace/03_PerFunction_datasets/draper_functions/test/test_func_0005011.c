supportedMandatoryAttributes(PRN_TYPE prnType, MSG_TYPE msgType, PRN_ROLE role,
	      unsigned long supportedFlag, char **flagName, void **response)
{
    int
        index;
    unsigned long
        result;
    PRN_FLAGMAP
	* map = 0;
    FLAGTABLE
	* table = 0;

    *flagName = 0;
    for (index = 0; index < (int) DIM_OF(prnMandatoryFlagMap); index++) {
	map = &prnMandatoryFlagMap[index];
	if ((map->prnType == prnType) && (map->msgType == msgType) &&
	    (map->prnRole == role))
	    break;
    }

    if (!map)
	return FALSE;


    result = supportedFlag & map->flag;
    if (result != map->flag) {


	result = result ^ map->flag;


	table = map->flagTable;
	for (index = 0; index < map->flagCount; index++) {
	    if (result & table[index].flag) {
		updateFlagName(flagName, table[index].flagName, 0);
		updateAttributeIdentifierList(table[index].tag, response);
	    }
	}
	return FALSE;
    } else
	return TRUE;
}

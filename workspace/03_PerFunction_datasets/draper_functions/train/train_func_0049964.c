layer_index(GVC_t *gvc, char *str, int all)
{

    int i;

    if (streq(str, "all"))
	return all;
    if (is_natural_number(str))
	return atoi(str);
    if (gvc->layerIDs)
	for (i = 1; i <= gvc->numLayers; i++)
	    if (streq(str, gvc->layerIDs[i]))
		return i;
    return -1;
}

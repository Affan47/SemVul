TranslateToHumanReadable(struct auto_string *str, map_tile * MapInfo, int LineLength, int layers)
{
	int col;
	int layer;

	for (col = 0; col < LineLength; col++) {
		for (layer = 0; layer < layers; layer++)
			autostr_append(str, "%3d ", MapInfo[col].floor_values[layer]);
	}

	autostr_append(str, "\n");
}

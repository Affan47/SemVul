ClearPlayground(void)
{
	int color, layer, row;

	for (color = YELLOW; color < TO_COLORS; color++)
		for (layer = 0; layer < NUM_LAYERS; layer++)
			for (row = 0; row < NUM_LINES; row++) {
				ActivationMap[color][layer][row] = INACTIVE;
				if (layer < TO_COLORS - 1)
					ToPlayground[color][layer][row] = CABLE;
				else
					ToPlayground[color][layer][row] = INACTIVE;
			}

	for (row = 0; row < NUM_LINES; row++)
		DisplayColumn[row] = row % 2;

}

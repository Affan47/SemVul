TileBuilder(std::string type) {
	Tile tile;
	if (type == "Ground") tile = Tile('.', COLOR_GREEN, !BLOCKS);
	else if (type == "Grass") tile = Tile(',', COLOR_GREEN, !BLOCKS);
	else if (type == "Plaza") tile = Tile(':', COLOR_GREEN, !BLOCKS);
	else if (type == "Floor") tile = Tile('.', COLOR_YELLOW, !BLOCKS);
	else if (type == "Marble floor") tile = Tile(':', COLOR_YELLOW, !BLOCKS);
	else if (type == "Wall") tile = Tile('#', COLOR_CYAN, BLOCKS);
	else if (type == "Church") tile = Tile('T', COLOR_CYAN, BLOCKS);
	else if (type == "Tree") tile = Tile('T', COLOR_GREEN, BLOCKS);
	else if (type == "Statue") tile = Tile('S', COLOR_YELLOW, BLOCKS);
	else if (type == "Chair") tile = Tile('h', COLOR_YELLOW, !BLOCKS);
	else if (type == "Table") tile = Tile('O', COLOR_YELLOW, BLOCKSMOVE);
	else if (type == "Barrel") tile = Tile('o', COLOR_YELLOW, BLOCKSMOVE);
	else if (type == "Closet") tile = Tile('%', COLOR_YELLOW, BLOCKSMOVE);
	else if (type == "Locked closet") tile = Tile('%', COLOR_YELLOW, BLOCKSMOVE);
	else if (type == "Left bed") {
		tile = Tile('[', COLOR_YELLOW, BLOCKSMOVE);
		tile.desc = "Bed";
	} else if (type == "Right bed") {
		tile = Tile(']', COLOR_YELLOW, BLOCKSMOVE);
		tile.desc = "Bed";
	} else if (type == "Window") {
		tile = Tile('-', COLOR_BLUE, BLOCKS);
		tile.blocks_vision_dist = 1;
	} else if (type == "Open door") {
		tile = Tile('/', COLOR_YELLOW, !BLOCKS);
	} else if (type.find("door") != std::string::npos) {
		tile = Tile('+', COLOR_RED, BLOCKS);
	}
	if (tile.desc.empty()) tile.desc = type;
	return tile;
}

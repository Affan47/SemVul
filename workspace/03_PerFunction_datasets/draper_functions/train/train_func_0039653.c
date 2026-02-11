specializeWalls() {


    map<string, TERRAIN> walls = {
        {"01011010", TERRAIN::C_WALL},
        {"01011000", TERRAIN::BT_WALL},
        {"01010010", TERRAIN::RT_WALL},
        {"01010000", TERRAIN::LR_WALL},
        {"01001010", TERRAIN::LT_WALL},
        {"01001000", TERRAIN::LL_WALL},
        {"01000010", TERRAIN::V_WALL},
        {"01000000", TERRAIN::V_WALL},
        {"00011010", TERRAIN::TT_WALL},
        {"00011000", TERRAIN::H_WALL},
        {"00010000", TERRAIN::H_WALL},
        {"00010010", TERRAIN::UR_WALL},
        {"00001010", TERRAIN::UL_WALL},
        {"00001000", TERRAIN::H_WALL},
        {"00000010", TERRAIN::V_WALL},
        {"00000000", TERRAIN::C_WALL},
    };

    for (int row = 0; row < MAP_HEIGHT; row++) {
        for (int col = 0; col < MAP_WIDTH; col++) {

            auto & t = _map[row][col];

            if (t->terrain() != TERRAIN::C_WALL) {
                continue;
            }

            int count = 7;
            bitset<8> edgeset;
            for (int y = row - 1; y < row + 2; y++) {

                if (y < 0 || y > MAP_HEIGHT - 1) {
                    count -= 3;
                    continue;
                }

                for (int x = col - 1; x < col + 2; x++) {
                    if (x < 0 || x > MAP_WIDTH - 1) {
                        count--;
                        continue;
                    }

                    if (y == row && x == col) {
                        continue;
                    }

                    if (_map[y][x]->isBlock()) {
                        edgeset.set(count);
                    }

                    auto item = _items.find(make_pair(y, x));
                    if (item != _items.end() &&
                    dynamic_cast<Door*>(item->second.get())) {
                        edgeset.set(count);
                    }

                    count--;
                }
            }

            for (auto& wall: walls) {
                bitset<8> mask(wall.first);
                if ((edgeset & mask) == mask) {
                    t->setTerrain(wall.second);
                }
            }
        }
    }
}

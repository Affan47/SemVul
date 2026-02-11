setOpenValue(int x, int y){


  char current = this->map[y*Grid::GRID_SIZE + x];

  if (current > 0) {
    if (current <= (Grid::MAX_VALUE - OPEN)) {
      this->map[y*Grid::GRID_SIZE + x] = OPEN + current;
    } else this->map[y*Grid::GRID_SIZE + x] = Grid::MAX_VALUE;
  } else {
    this->map[y*Grid::GRID_SIZE + x] = OPEN;
  }
}

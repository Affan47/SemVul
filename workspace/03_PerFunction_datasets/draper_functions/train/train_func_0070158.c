_add_untagged_neighbours_to_tile_union(
               const int tile_index,
	       vector<int> & tile_union, int & n_near_tiles)  {
  for (Tile ** near_tile = _tiles[tile_index].begin_tiles;
       near_tile != _tiles[tile_index].end_tiles; near_tile++){
    if (! (*near_tile)->tagged) {
      (*near_tile)->tagged = true;

      tile_union[n_near_tiles] = *near_tile - & _tiles[0];
      n_near_tiles++;
    }
  }
}

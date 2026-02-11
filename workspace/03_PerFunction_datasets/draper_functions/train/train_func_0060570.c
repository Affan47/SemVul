operator=(const R2Grid& voxels)
{

  grid_resolution[0] = voxels.grid_resolution[0];
  grid_resolution[1] = voxels.grid_resolution[1];
  grid_row_size = voxels.grid_row_size;
  grid_size = voxels.grid_size;


  if (grid_values) delete [] grid_values;
  if (grid_size == 0) grid_values = NULL;
  else grid_values = new RNScalar [ grid_size ];
  assert(!grid_size || grid_values);
  for (int i = 0; i < grid_size; i++) {
    grid_values[i] = voxels.grid_values[i];
  }


  grid_to_world_transform = voxels.grid_to_world_transform;
  world_to_grid_transform = voxels.world_to_grid_transform;
  world_to_grid_scale_factor = voxels.world_to_grid_scale_factor;


  return *this;
}

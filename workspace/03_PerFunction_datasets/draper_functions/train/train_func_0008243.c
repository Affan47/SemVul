setGridHData(int nof_ids, int* grid_h_ids, int* mesh_indices, bool force)
{
  if ( gridHData == NULL ) {

    if ( nof_ids > 0 ) {
      gridHData = new BodyElementGridHData();

    } else {
      return;
    }
  }

  gridHData->setData(nof_ids, grid_h_ids, mesh_indices);
}

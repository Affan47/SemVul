_dxfFreeSimplificationDataStructure(SimpData *simp_data, float *vertex_data, float *old_positional_error)
{

  if (simp_data->edge2index)
    {
      DXFree((Pointer) simp_data->edge2index);
      simp_data->edge2index = NULL;
    }

  if (simp_data->index2edge)
    {
      DXFree((Pointer) simp_data->index2edge);
      simp_data->index2edge = NULL;
    }

  if (simp_data->edge_father)
    {
      DXFree((Pointer) simp_data->edge_father);
      simp_data->edge_father = NULL;
    }

  if (simp_data->normal)
    {
      DXFree((Pointer) simp_data->normal);
      simp_data->normal = NULL;
    }

  if (simp_data->area)
    {
      DXFree((Pointer) simp_data->area);
      simp_data->area = NULL;
    }

  if (simp_data->compactness)
    {
      DXFree((Pointer) simp_data->compactness);
      simp_data->compactness = NULL;
    }

  if (simp_data->valence)
    {
      DXFree((Pointer) simp_data->valence);
      simp_data->valence = NULL;
    }

  if (simp_data->boundary_vert)
    {
      DXFree((Pointer) simp_data->boundary_vert);
      simp_data->boundary_vert = NULL;
    }

  if (simp_data->err_volume && simp_data->err_volume != old_positional_error)
    {
      DXFree((Pointer) simp_data->err_volume);
      simp_data->err_volume = old_positional_error;
    }

  if (simp_data->tol_volume)
    {
      DXFree((Pointer) simp_data->tol_volume);
      simp_data->tol_volume = NULL;
    }

  if (simp_data->vx_data && simp_data->vx_data != vertex_data)
    {
      DXFree((Pointer) simp_data->vx_data);
      simp_data->vx_data = vertex_data;
    }

  if (simp_data->vx_data_error)
    {
      DXFree((Pointer) simp_data->vx_data_error);
      simp_data->vx_data_error = NULL;
    }

  if (simp_data->vx_data_potential_values)
    {
      DXFree((Pointer)simp_data->vx_data_potential_values);
      simp_data->vx_data_potential_values = NULL;
    }

  if (simp_data->edge_heap)
    {
      DXFree((Pointer) simp_data->edge_heap);
      simp_data->edge_heap = NULL;
    }

  return 1;
}

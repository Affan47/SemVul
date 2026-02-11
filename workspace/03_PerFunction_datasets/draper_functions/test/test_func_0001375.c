Copy (Shape * who)
{
  if (who == NULL)
    {
      Reset (0, 0);
      return;
    }
  MakePointData (false);
  MakeEdgeData (false);
  MakeSweepSrcData (false);
  MakeSweepDestData (false);
  MakeRasterData (false);
  MakeQuickRasterData (false);
  MakeBackData (false);

  delete sTree;
  sTree = NULL;
  delete sEvts;
  sEvts = NULL;

  Reset (who->numberOfPoints(), who->numberOfEdges());
  type = who->type;
  _need_points_sorting = who->_need_points_sorting;
  _need_edges_sorting = who->_need_edges_sorting;
  _has_points_data = false;
  _point_data_initialised = false;
  _has_edges_data = false;
  _has_sweep_src_data = false;
  _has_sweep_dest_data = false;
  _has_raster_data = false;
  _has_quick_raster_data = false;
  _has_back_data = false;
  _has_voronoi_data = false;
  _bbox_up_to_date = false;

  _pts = who->_pts;
  _aretes = who->_aretes;
}

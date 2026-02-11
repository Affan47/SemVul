AddEdge (int st, int en)
{
  if (st == en)
    return -1;
  if (st < 0 || en < 0)
    return -1;
  type = shape_graph;
  if (numberOfEdges() >= maxAr)
    {
      maxAr = 2 * numberOfEdges() + 1;
      if (_has_edges_data)
        eData.resize(maxAr);
      if (_has_sweep_src_data)
        swsData.resize(maxAr);
      if (_has_sweep_dest_data)
        swdData.resize(maxAr);
      if (_has_raster_data)
        swrData.resize(maxAr);
      if (_has_back_data)
        ebData.resize(maxAr);
      if (_has_voronoi_data)
        voreData.resize(maxAr);
    }

  dg_arete a;
  a.dx = Geom::Point(0, 0);
  a.st = a.en = -1;
  a.prevS = a.nextS = -1;
  a.prevE = a.nextE = -1;
  if (st >= 0 && en >= 0) {
    a.dx = getPoint(en).x - getPoint(st).x;
  }

  _aretes.push_back(a);
  int const n = numberOfEdges() - 1;

  ConnectStart (st, n);
  ConnectEnd (en, n);
  if (_has_edges_data)
    {
      eData[n].weight = 1;
      eData[n].rdx = getEdge(n).dx;
    }
  if (_has_sweep_src_data)
    {
      swsData[n].misc = NULL;
      swsData[n].firstLinkedPoint = -1;
    }
  if (_has_back_data)
    {
      ebData[n].pathID = -1;
      ebData[n].pieceID = -1;
      ebData[n].tSt = ebData[n].tEn = 0;
    }
  if (_has_voronoi_data)
    {
      voreData[n].leF = -1;
      voreData[n].riF = -1;
    }
  _need_edges_sorting = true;
  return n;
}

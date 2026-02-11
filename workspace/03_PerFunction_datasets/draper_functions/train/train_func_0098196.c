exportToStreamAllCurvesTogether(Q3TextStream& str, CoordSettings coord,
  GridMeshSettings grid, ExportSettings xport, int xPrecision, int yPrecision)
{

  QList<double> xUsed = ascendingXValuesList(coord, grid, xport, xPrecision);

  if (xport.header != HeaderNone)
  {

    str << exportHeaderPrefix(coord, xport);
    for (PointSetList::iterator itrG = curveList.begin(); itrG != curveList.end(); ++itrG)
      if ((*itrG).getExport())
      {
        str << delimiter(xport.delimiters);
        str << (*itrG).exportCurveHeader(xport);
      }
    str << "\n";
  }


  bool useInterpolation = (xport.pointsSelection != XYFromAllCurves);


  QString xNew;
  QList<double>::iterator itrX;
  for (itrX = xUsed.begin(); itrX != xUsed.end(); ++itrX)
  {
    xNew.setNum(*itrX, 'g', xPrecision);

    str << xNew;
    for (PointSetList::iterator itrG = curveList.begin(); itrG != curveList.end(); ++itrG)
      if ((*itrG).getExport())
      {
        str << delimiter(xport.delimiters);
        str << (*itrG).exportCurvePoint(*itrX, coord, useInterpolation, yPrecision);
      }

    str << "\n";
  }
}

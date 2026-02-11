initGeometryInfo()
{
  curveGeometryDlg = new GeometryDlg(this, true);
  CHECK_PTR_ENGAUGE(curveGeometryDlg);
  connect(curveGeometryDlg, SIGNAL(hideGeometry()), this, SLOT(slotHideCurveGeometry()));

  measureGeometryDlg = new GeometryDlg(this, false);
  CHECK_PTR_ENGAUGE(measureGeometryDlg);
  connect(measureGeometryDlg, SIGNAL(hideGeometry()), this, SLOT(slotHideMeasureGeometry()));

  noGeometryInfo();
}

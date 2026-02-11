makeSegments(QImage &imageProcessed, SegmentSettings seg)
{
  segments.clear();


  int madeLines = 0;
  int shortLines = 0;
  int foldedLines = 0;


  const bool useDlg = true;


  int width = imageProcessed.width();
  int height = imageProcessed.height();

  QProgressDialog* dlg;
  if (useDlg)
  {

    dlg = new QProgressDialog("Scanning segments in image", "Cancel", 0, width);
    CHECK_PTR_ENGAUGE(dlg);
    dlg->setCaption(QString("Progress"));
    dlg->show();
  }

  bool* lastBool = new bool [height];
  CHECK_PTR_ENGAUGE(lastBool);
  bool* currBool = new bool [height];
  CHECK_PTR_ENGAUGE(currBool);
  bool* nextBool = new bool [height];
  CHECK_PTR_ENGAUGE(nextBool);
  Segment** lastSegment = new Segment* [height];
  CHECK_PTR_ENGAUGE(lastSegment);
  Segment** currSegment = new Segment* [height];
  CHECK_PTR_ENGAUGE(currSegment);

  Discretize discretize;
  loadBool(&discretize, lastBool, &imageProcessed, -1);
  loadBool(&discretize, currBool, &imageProcessed, 0);
  loadBool(&discretize, nextBool, &imageProcessed, 1);
  loadSegment(lastSegment, height);

  for (int x = 0; x < width; x++)
  {
    if (useDlg)
    {

      dlg->setValue(x);
      qApp->processEvents();

      if (dlg->wasCanceled())

        break;
    }

    matchRunsToSegments(x, height, lastBool, lastSegment, currBool, currSegment, nextBool, seg,
      &madeLines, &foldedLines, &shortLines);


    scrollBool(lastBool, currBool, height);
    scrollBool(currBool, nextBool, height);
    if (x + 1 < width)
      loadBool(&discretize, nextBool, &imageProcessed, x + 1);
    scrollSegment(lastSegment, currSegment, height);
  }

  if (useDlg)
  {
    dlg->setValue(width);
    delete dlg;
  }

  DigitDebug::scanning(QString("segment lines created ") + QString::number(madeLines) +
    QString(", too short so removed ") + QString::number(shortLines) +
    QString(", folded together ") + QString::number(foldedLines));

  delete[] lastBool;
  delete[] currBool;
  delete[] nextBool;
  delete[] lastSegment;
  delete[] currSegment;
}

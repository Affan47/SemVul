snapToPaperAndFrame()
{
  double snapDist = iSnap.iSnapDistance / iZoom;
  double d = snapDist;
  Vector fifi = iMousePos;
  const Layout *layout = iCascade->findLayout();
  Rect paper = layout->paper();
  Rect frame(Vector::ZERO, layout->iFrameSize);


  if (iSnap.iSnap & Snap::ESnapVtx) {
    paper.bottomLeft().snap(iMousePos, fifi, d);
    paper.topRight().snap(iMousePos, fifi, d);
    paper.topLeft().snap(iMousePos, fifi, d);
    paper.bottomRight().snap(iMousePos, fifi, d);
    frame.bottomLeft().snap(iMousePos, fifi, d);
    frame.topRight().snap(iMousePos, fifi, d);
    frame.topLeft().snap(iMousePos, fifi, d);
    frame.bottomRight().snap(iMousePos, fifi, d);
  }


  if (d < snapDist) {
    iMousePos = fifi;
    return true;
  }


  if (iSnap.iSnap & Snap::ESnapBd) {
    Segment(paper.bottomLeft(), paper.bottomRight()).snap(iMousePos, fifi, d);
    Segment(paper.bottomRight(), paper.topRight()).snap(iMousePos, fifi, d);
    Segment(paper.topRight(), paper.topLeft()).snap(iMousePos, fifi, d);
    Segment(paper.topLeft(), paper.bottomLeft()).snap(iMousePos, fifi, d);
    Segment(frame.bottomLeft(), frame.bottomRight()).snap(iMousePos, fifi, d);
    Segment(frame.bottomRight(), frame.topRight()).snap(iMousePos, fifi, d);
    Segment(frame.topRight(), frame.topLeft()).snap(iMousePos, fifi, d);
    Segment(frame.topLeft(), frame.bottomLeft()).snap(iMousePos, fifi, d);
  }

  if (d < snapDist) {
    iMousePos = fifi;
    return true;
  }

  return true;
}

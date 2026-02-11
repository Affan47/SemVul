GraphicToScreen
(Graphic* gr, float xgr, float ygr, float& xscreen, float& yscreen)
{
  if (!gr) {
    xscreen = Math::round(xgr);
    yscreen = Math::round(ygr);
    return;
  }


  float xdrawgr, ydrawgr;
  if (gr->GetTransformer())
    gr->GetTransformer()->Transform(xgr, ygr, xdrawgr, ydrawgr);


  DrawingToScreen(xdrawgr, ydrawgr, xscreen, yscreen);
  return;
}

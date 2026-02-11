createRectangles(const Envelope& env, int nRect, double rectSize,
                        vector<const Geometry*>& rectList)
  {
    int nSide =  1 + (int)sqrt((double) nRect);
    double dx = env.getWidth() / nSide;
    double dy = env.getHeight() / nSide;

    for (int i = 0; i < nSide; i++) {
      for (int j = 0; j < nSide; j++) {
        double baseX = env.getMinX() + i * dx;
        double baseY = env.getMinY() + j * dy;
        Envelope envRect(
            baseX, baseX + dx,
            baseY, baseY + dy);
        Geometry* rect = fact.toGeometry(&envRect);
        rectList.push_back(rect);
      }
    }
  }

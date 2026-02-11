setupScreenParams(double hDPI, double vDPI) {
  screenParams.size = globalParams->getScreenSize();
  screenParams.dotRadius = globalParams->getScreenDotRadius();
  screenParams.gamma = (SplashCoord)globalParams->getScreenGamma();
  screenParams.blackThreshold =
      (SplashCoord)globalParams->getScreenBlackThreshold();
  screenParams.whiteThreshold =
      (SplashCoord)globalParams->getScreenWhiteThreshold();
  switch (globalParams->getScreenType()) {
  case screenDispersed:
    screenParams.type = splashScreenDispersed;
    if (screenParams.size < 0) {
      screenParams.size = 4;
    }
    break;
  case screenClustered:
    screenParams.type = splashScreenClustered;
    if (screenParams.size < 0) {
      screenParams.size = 10;
    }
    break;
  case screenStochasticClustered:
    screenParams.type = splashScreenStochasticClustered;
    if (screenParams.size < 0) {
      screenParams.size = 64;
    }
    if (screenParams.dotRadius < 0) {
      screenParams.dotRadius = 2;
    }
    break;
  case screenUnset:
  default:


    if (hDPI > 299.9 && vDPI > 299.9) {
      screenParams.type = splashScreenStochasticClustered;
      if (screenParams.size < 0) {
	screenParams.size = 64;
      }
      if (screenParams.dotRadius < 0) {
	screenParams.dotRadius = 2;
      }
    } else {
      screenParams.type = splashScreenDispersed;
      if (screenParams.size < 0) {
	screenParams.size = 4;
      }
    }
  }
}

scaleHeight(float ratio)
{
#if COIN_DEBUG
  if (ratio<0.0f) {
    SoDebugError::postWarning("SbViewportRegion::scaleheight",
                              "ratio (%f) should be >=0.0f. Clamped to 0.0f.",
                              ratio);
    ratio=0.0f;
  }
#endif

  float oldh = this->vpsize[1];
  this->vpsize[1] *= ratio;
  this->vporigin[1] -= (this->vpsize[1] - oldh) / 2.0f;

  if(this->vpsize[1] > 1.0f) this->vpsize[1] = 1.0f;
  if(this->vporigin[1] < 0.0f) this->vporigin[1] = 0.0f;
}

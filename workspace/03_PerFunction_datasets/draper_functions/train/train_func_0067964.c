setHSVValue(float hue, float saturation,
                      float value, float alpha)
{
#if COIN_DEBUG
  if (!(hue>=0.0f && hue<=1.0f)) {
    SoDebugError::postWarning("SbColor4f::setHSVValue",
                              "'hue' (%f) not within [0.0,1.0]; clamping.",
                              hue);
    if (hue<0.0f) hue=0.0f;
    else if (hue>1.0f) hue=1.0f;
  }

  if (!(saturation>=0.0f && saturation<=1.0f)) {
    SoDebugError::postWarning("SbColor4f::setHSVValue",
                              "'saturation' (%f) not within [0.0,1.0]; "
                              "clamping.", saturation);
    if (saturation<0.0f) saturation=0.0f;
    else if (saturation>1.0f) saturation=1.0f;
  }

  if (!(value>=0.0f && value<=1.0f)) {
    SoDebugError::postWarning("SbColor4f::setHSVValue",
                              "'value' (%f) not within [0.0,1.0]; clamping.",
                              value);
    if (value<0.0f) value=0.0f;
    else if (value>1.0f) value=1.0f;
  }
  if (!(alpha >= 0.0f && alpha <= 1.0f)) {
    SoDebugError::postWarning("SbColor4f::setHSVValue",
                              "'alpha' (%f) not within [0.0,1.0]; clamping.",
                              alpha);
    alpha = SbClamp(alpha, 0.0f, 1.0f);
  }

#endif

  SbColor col;
  col.setHSVValue(hue, saturation, value);
  this->vec[0] = col[0];
  this->vec[1] = col[1];
  this->vec[2] = col[2];
  this->vec[3] = alpha;
  return *this;
}

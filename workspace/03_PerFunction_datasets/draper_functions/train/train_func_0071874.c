remainingRect(DrawParams* dp)
{
  if (!dp) dp = drawParams();

  if ((_usedTopLeft >0) ||
      (_usedTopCenter >0) ||
      (_usedTopRight >0)) {
    if (dp->rotated())
      _rect.setLeft(_rect.left() + _fontHeight);
    else
      _rect.setTop(_rect.top() + _fontHeight);
  }

  if ((_usedBottomLeft >0) ||
      (_usedBottomCenter >0) ||
      (_usedBottomRight >0)) {
    if (dp->rotated())
      _rect.setRight(_rect.right() - _fontHeight);
    else
      _rect.setBottom(_rect.bottom() - _fontHeight);
  }
  return _rect;
}

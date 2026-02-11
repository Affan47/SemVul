endElement(const EndElementEvent &event)
{
  if (mustOmitEndTag_)
    mustOmitEndTag_ = 0;
  else {
    if (outputState_ == pendingRe) {
      outputRe();
      outputRe();
    }
    else if (isElementContentStack_[isElementContentStack_.size() - 1])
      outputRe();
    os() << "</" << event.gi << '>';
  }
  outputState_ = outputStateStack_[outputStateStack_.size() - 1];
  outputStateStack_.resize(outputStateStack_.size() - 1);
  parseMode_ = normalMode;
  isElementContentStack_.resize(isElementContentStack_.size() - 1);
}

phiY() const {
  return (yy() == 0.0 && xy() == 0.0) ? 0.0 : std::atan2(yy(),xy());
}

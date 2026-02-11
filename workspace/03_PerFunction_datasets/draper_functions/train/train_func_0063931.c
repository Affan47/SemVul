reset(const Char *start,
			const Char *end)
{
  origin_ = origin_->copy();
  start_ = start;
  end_ = end;
  cur_ = start_;
  startLocation_ = Location(origin_.pointer(), 0);
  multicode_ = 0;
  scanSuppress_ = 0;
  markupScanTable_.clear();
}

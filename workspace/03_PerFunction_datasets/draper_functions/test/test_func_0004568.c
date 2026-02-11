text(int textNo) const
{
  if (textNo == 0) {
    if (!_f)
      return QObject::tr("(no function)");

    return _f->prettyName();
  }

  if (!_f) return QString();

  if (textNo == 2) return _f->prettyLocation();
  if (textNo == 3) return _f->calledCount().pretty();
  if (textNo != 1) return QString();

  EventType* ct = ((CallMapView*)widget())->eventType();
  ProfileCostArray* t      = ((CallMapView*)widget())->totalCost();

  if (GlobalConfig::showPercentage()) {
      double sum, total = t->subCost(ct);
      if (total == 0.0)
	  sum = 100.0;
      else
	  sum = 100.0 * _f->inclusive()->subCost(ct) / total;

      return QString("%1 %")
	  .arg(sum, 0, 'f', GlobalConfig::percentPrecision());
  }
  return _f->inclusive()->prettySubCost(ct);
}

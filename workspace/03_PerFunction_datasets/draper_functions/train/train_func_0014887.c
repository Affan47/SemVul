operator<< (WarningConsolidation& wcc, const Dynare::location& loc)
{
  if (wcc.no_warn)
    return wcc;

  stringstream ostr;
  Dynare::position last = loc.end - 1;
  ostr << loc.begin;
  if (last.filename
      && (!loc.begin.filename
          || *loc.begin.filename != *last.filename))
    ostr << '-' << last;
  else if (loc.begin.line != last.line)
    ostr << '-' << last.line  << '.' << last.column;
  else if (loc.begin.column != last.column)
    ostr << '-' << last.column;

  cerr << ostr.str();
  wcc.addWarning(ostr.str());
  return wcc;
}

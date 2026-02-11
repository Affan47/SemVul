getRangeQuery(const TCHAR* _field, TCHAR* part1, TCHAR* part2, const bool inclusive)
{
  if (lowercaseExpandedTerms) {
    _tcslwr(part1);
    _tcslwr(part2);
  }

  TCHAR* _part1 = part1, *_part2 = part2;
  try {


      const int64_t d1 = CL_NS(document)::DateTools::stringToTime(part1);
      int64_t d2 = CL_NS(document)::DateTools::stringToTime(part2);
      if (inclusive) {


          d2 = CL_NS(document)::DateTools::timeMakeInclusive(d2);
      }

      CL_NS(document)::DateTools::Resolution resolution = getDateResolution(_field);
      if (resolution == CL_NS(document)::DateTools::NO_RESOLUTION) {


          _part1 = CL_NS(document)::DateField::timeToString(d1);
          _part2 = CL_NS(document)::DateField::timeToString(d2);
      } else {
          _part1 = CL_NS(document)::DateTools::timeToString(d1, resolution);
          _part2 = CL_NS(document)::DateTools::timeToString(d2, resolution);
      }
  }
  catch (...) { }

  if(useOldRangeQuery)
  {
      Term* t1 = _CLNEW Term(_field,part1);
      Term* t2 = _CLNEW Term(_field,part2);
      Query* ret = _CLNEW RangeQuery(t1, t2, inclusive);
      _CLDECDELETE(t1);
      _CLDECDELETE(t2);


      if (part1 != _part1) _CLDELETE_LCARRAY(_part1);
      if (part2 != _part2) _CLDELETE_LCARRAY(_part2);

      return ret;
  }
  else
  {
      Query* q = _CLNEW ConstantScoreRangeQuery(_field,part1,part2,inclusive,inclusive);


      if (part1 != _part1) _CLDELETE_LCARRAY(_part1);
      if (part2 != _part2) _CLDELETE_LCARRAY(_part2);

      return q;
  }
}

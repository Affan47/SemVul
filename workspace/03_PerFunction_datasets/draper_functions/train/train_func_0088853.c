readLineSegment( char *line)
{
  if (line == NULL) {
    return false;
  }

  int x1 = 0;
  int y1 = 0;
  int x2 = 0;
  int y2 = 0;

  bool isSuccess  = true;
  size_t lineLen     = strlen(line) + 1;
  int startIndex  = 0;
  size_t parsedCount = 0;

  isSuccess = parseNumber(&line[startIndex], lineLen, &parsedCount, &x1);

  startIndex += parsedCount;
  lineLen -= parsedCount;

  if (!isSuccess) {
    ArLog::log(ArLog::Normal,
               "%sArMapScan::readLineSegment error parsing x1 (startIndex = %i, lineLen = %i) in '%s'",
               myLogPrefix.c_str(), startIndex, lineLen, line);
    return false;
  }


  isSuccess = parseWhitespace(&line[startIndex], lineLen, &parsedCount);

  startIndex += parsedCount;
  lineLen -= parsedCount;

  if (!isSuccess) {
    ArLog::log(ArLog::Normal,
               "%sArMapScan::readLineSegment error parsing first whitespace (startIndex = %i, lineLen = %i) in '%s'",
               myLogPrefix.c_str(), startIndex, lineLen, line);
    return false;
  }


  isSuccess = parseNumber(&line[startIndex], lineLen, &parsedCount, &y1);

  startIndex += parsedCount;
  lineLen -= parsedCount;

  if (!isSuccess) {
    ArLog::log(ArLog::Normal,
               "%sArMapScan::readLineSegment error parsing y1 (startIndex = %i, lineLen = %i) in '%s'",
               myLogPrefix.c_str(), startIndex, lineLen, line);
    return false;
  }


  isSuccess = parseWhitespace(&line[startIndex], lineLen, &parsedCount);

  startIndex += parsedCount;
  lineLen -= parsedCount;

  if (!isSuccess) {
    ArLog::log(ArLog::Normal,
               "%sArMapScan::readLineSegment error parsing second whitespace (startIndex = %i, lineLen = %i) in '%s'",
               myLogPrefix.c_str(), startIndex, lineLen, line);
    return false;
  }


  isSuccess = parseNumber(&line[startIndex], lineLen, &parsedCount, &x2);

  startIndex += parsedCount;
  lineLen -= parsedCount;

  if (!isSuccess) {
    ArLog::log(ArLog::Normal,
               "%sArMapScan::readLineSegment error parsing x2 (startIndex = %i, lineLen = %i) in '%s'",
               myLogPrefix.c_str(), startIndex, lineLen, line);
    return false;
  }


  isSuccess = parseWhitespace(&line[startIndex], lineLen, &parsedCount);

  startIndex += parsedCount;
  lineLen -= parsedCount;

  if (!isSuccess) {
    ArLog::log(ArLog::Normal,
               "%sArMapScan::readLineSegment error parsing third whitespace (startIndex = %i, lineLen = %i) in '%s'",
               myLogPrefix.c_str(), startIndex, lineLen, line);
    return false;
  }


  isSuccess = parseNumber(&line[startIndex], lineLen, &parsedCount, &y2);

  startIndex += parsedCount;
  lineLen -= parsedCount;

  if (!isSuccess) {
    ArLog::log(ArLog::Normal,
               "%sArMapScan::readLineSegment error parsing y2 (startIndex = %i, lineLen = %i) in '%s'",
               myLogPrefix.c_str(), startIndex, lineLen, line);
    return false;
  }


  loadLineSegment(x1, y1, x2, y2);

  return true;

}

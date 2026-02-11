advanceParse(logParseToken *current, char *parsePoint, char **parseEndPoint, logdata *data) {
  logParseToken *next = current->next;


  char *matchStrings[2] = {NULL, NULL};
  int matchStringLengths[2] = {0, 0};
  int stringsToAlwaysMatch = 0;

  if (current->string_len_after) {
    matchStrings[0] = current->string_after;
    matchStringLengths[0] = current->string_len_after;
    stringsToAlwaysMatch = 1;
  }


  while(1) {
    debug_print("Going for the next token (%s%%%c%s), it is %s token\n",
        next ? next->string_before : "",
        next ? next->formatChar: '0',
        next ? next->string_after: "",
        next ? (next->optional ? "an optional" : "a mandatory") : "a null"
        );


    int stringsToMatch = stringsToAlwaysMatch;
    if (next && next->string_len_before) {
      matchStrings[stringsToMatch] = next->string_before;
      matchStringLengths[stringsToMatch] = next->string_len_before;
      stringsToMatch++;
    }
    for(int s = 0; s < stringsToMatch; s++) {
      debug_print("We need to match \"%s\"\n", matchStrings[s]);
    }

    char *curEndPoint = parsePoint;
    while (curEndPoint) {
      debug_print("Seeking from \"%s\"\n", curEndPoint);
      char *searchPosition = curEndPoint;
      int curString = 0;
      if (!current->deterministic) {
        if (stringsToMatch) {
          debug_print("Seeking \"%s\"\n", matchStrings[0]);

          curEndPoint = strstr(curEndPoint,matchStrings[0]);
          if (!curEndPoint) {

            break;
          }

          searchPosition = curEndPoint + matchStringLengths[0];
          curString = 1;
        } else if (!next) {

          while(*curEndPoint!= '\0') curEndPoint++;
          searchPosition = curEndPoint;
        }
      }

      int matched = 1;

      for(int s = curString; s < stringsToMatch; s++) {
        debug_print("Skipping \"%s\" at \"%s\"\n", matchStrings[s], searchPosition);
        searchPosition = skipString(searchPosition, matchStrings[s], matchStringLengths[s]);
        if (!searchPosition) {
          matched = 0;
          break;
        }
      }

      if (matched) {
        debug_print("Matched at \"%s\"\n", searchPosition);
        char *parseResult = next ? parseLogToken(next, searchPosition, data) : searchPosition;
        if (parseResult && *parseResult == '\0') {
          *parseEndPoint = curEndPoint;
          return parseResult;
        }
      }
      if (current->deterministic) break;
      curEndPoint++;
    }

    if (!next) break;
    if (next->optional) {
      next= next->next;
    } else {
      break;
    }
  }

  return NULL;
}

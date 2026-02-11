GetIndex(const char* name) {
    if (strcmp(name, "liveedit") == 0) return 0;
    if (strcmp(name, "mirror") == 0) return 1;
    if (strcmp(name, "debug") == 0) return 2;
    if (strcmp(name, "runtime") == 0) return 3;
    if (strcmp(name, "v8natives") == 0) return 4;
    if (strcmp(name, "array") == 0) return 5;
    if (strcmp(name, "string") == 0) return 6;
    if (strcmp(name, "uri") == 0) return 7;
    if (strcmp(name, "math") == 0) return 8;
    if (strcmp(name, "messages") == 0) return 9;
    if (strcmp(name, "apinatives") == 0) return 10;
    if (strcmp(name, "date") == 0) return 11;
    if (strcmp(name, "regexp") == 0) return 12;
    if (strcmp(name, "json") == 0) return 13;
    return -1;
  }

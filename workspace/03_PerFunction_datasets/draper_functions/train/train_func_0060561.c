dump(orbOptions::sequenceString& result) {
    const char* v;

    v = the_fileDefaultInitRef;
    orbOptions::addKVString("DefaultInitRef (file)", v ? v : "", result);

    v = the_argsDefaultInitRef;
    orbOptions::addKVString("DefaultInitRef (args)", v ? v : "", result);
  }
}

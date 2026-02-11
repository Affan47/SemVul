scanningFile(const FilePart* file, uint64 offInFile) {
    if (!printProgress) return;
    string m;
    append(m, 100 * offInFile / file->size(), 3);
    m += '%';
    append(m, offInFile / 1024, 8);
    m += "k/";
    append(m, file->size() / 1024);
    m += 'k';
    if (m.size() < 3+1+8+2+8+1)
      m += "          " + 10 - (3+1+8+2+8+1 - m.size());
    Paranoid(m.length() == PROGRESS_WIDTH);
    m += _("scanning");
    m += " `";
    m += file->leafName();
    m += '\'';
    print(m, false);
  }

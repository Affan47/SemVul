save(const string &file, bool bin)
{
  ofstream ofs(file.c_str(), ios::out);
  if (!ofs) {
    cerr << "Failed to open " << file << endl;
    exit(1);
  }
  ostream *os = &ofs;
  save(os, bin);
  ofs.close();
}

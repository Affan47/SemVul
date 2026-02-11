gmGenFileWriterOpen(const char* filename, int hdfs) {
  return new GM_Writer(filename, (bool)hdfs);

}

registerFile (const std::string &filename) {
    LineMap *m = new LineMap() ;
    files[filename] = m ;
    return m ;
}

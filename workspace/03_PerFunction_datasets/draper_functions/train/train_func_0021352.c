make_raw(std::shared_ptr<LargeRAWFile> source, uint64_t n_components,
         size_t csize) {
  typedef std::vector<std::shared_ptr<LargeRAWFile>> files;
  const size_t nc = static_cast<size_t>(n_components);
  std::vector<std::shared_ptr<LargeRAWFile>> components(nc);

  for(files::iterator f=components.begin(); f != components.end(); ++f) {
    std::ofstream ofs;
    std::string filename = mk_tmpfile(ofs, std::ios::out | std::ios::binary);
    *f = std::shared_ptr<LargeRAWFile>(new TempFile(filename));
    (*f)->Open(true);
  }

  source->SeekStart();

  std::shared_ptr<unsigned char> data(new unsigned char[csize],
                                      nonstd::DeleteArray<unsigned char>());
  size_t bytes=1;
  do {
    for(size_t c=0; c < nc; ++c) {
      bytes = source->ReadRAW(data.get(), csize);
      if(bytes) {
        components[c]->WriteRAW(data.get(), csize);
      }
    }
  } while(bytes > 0);


  for(files::iterator f=components.begin(); f != components.end(); ++f) {
    (*f)->Close();
    (*f)->Open();
  }

  return components;
}

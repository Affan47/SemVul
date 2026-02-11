ExpandResponseFiles(unsigned argc, char** argv,
                                std::vector<char*>& newArgv) {
  for (unsigned i = 1; i != argc; ++i) {
    char *arg = argv[i];

    if (arg[0] == '@') {
      sys::PathWithStatus respFile(++arg);


      const sys::FileStatus *FileStat = respFile.getFileStatus();
      if (FileStat && FileStat->getSize() != 0) {


        OwningPtr<MemoryBuffer> respFilePtr;
        if (!MemoryBuffer::getFile(respFile.c_str(), respFilePtr)) {
          ParseCStringVector(newArgv, respFilePtr->getBufferStart());
          continue;
        }
      }
    }
    newArgv.push_back(strdup(arg));
  }
}

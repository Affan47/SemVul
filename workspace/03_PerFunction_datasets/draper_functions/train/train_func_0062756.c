ExtractMappedBlocksFromModule(const
                                                 std::vector<BasicBlock*> &BBs,
                                                 Module *M) {
  sys::Path uniqueFilename(OutputPrefix + "-extractblocks");
  std::string ErrMsg;
  if (uniqueFilename.createTemporaryFileOnDisk(true, &ErrMsg)) {
    outs() << "*** Basic Block extraction failed!\n";
    errs() << "Error creating temporary file: " << ErrMsg << "\n";
    EmitProgressBitcode(M, "basicblockextractfail", true);
    return 0;
  }
  sys::RemoveFileOnSignal(uniqueFilename);

  std::string ErrorInfo;
  tool_output_file BlocksToNotExtractFile(uniqueFilename.c_str(), ErrorInfo);
  if (!ErrorInfo.empty()) {
    outs() << "*** Basic Block extraction failed!\n";
    errs() << "Error writing list of blocks to not extract: " << ErrorInfo
           << "\n";
    EmitProgressBitcode(M, "basicblockextractfail", true);
    return 0;
  }
  for (std::vector<BasicBlock*>::const_iterator I = BBs.begin(), E = BBs.end();
       I != E; ++I) {
    BasicBlock *BB = *I;


    if (!BB->hasName()) BB->setName("tmpbb");
    BlocksToNotExtractFile.os() << BB->getParent()->getNameStr() << " "
                                << BB->getName() << "\n";
  }
  BlocksToNotExtractFile.os().close();
  if (BlocksToNotExtractFile.os().has_error()) {
    errs() << "Error writing list of blocks to not extract: " << ErrorInfo
           << "\n";
    EmitProgressBitcode(M, "basicblockextractfail", true);
    BlocksToNotExtractFile.os().clear_error();
    return 0;
  }
  BlocksToNotExtractFile.keep();

  std::string uniqueFN = "--extract-blocks-file=" + uniqueFilename.str();
  const char *ExtraArg = uniqueFN.c_str();

  std::vector<std::string> PI;
  PI.push_back("extract-blocks");
  Module *Ret = runPassesOn(M, PI, false, 1, &ExtraArg);

  uniqueFilename.eraseFromDisk();

  if (Ret == 0) {
    outs() << "*** Basic Block extraction failed, please report a bug!\n";
    EmitProgressBitcode(M, "basicblockextractfail", true);
  }
  return Ret;
}

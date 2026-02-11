mergeSampleProfile(const cl::list<std::string> &Inputs,
                               StringRef OutputFilename,
                               sampleprof::SampleProfileFormat OutputFormat) {
  using namespace sampleprof;
  auto WriterOrErr = SampleProfileWriter::create(OutputFilename, OutputFormat);
  if (std::error_code EC = WriterOrErr.getError())
    exitWithError(EC.message(), OutputFilename);

  auto Writer = std::move(WriterOrErr.get());
  StringMap<FunctionSamples> ProfileMap;
  SmallVector<std::unique_ptr<sampleprof::SampleProfileReader>, 5> Readers;
  for (const auto &Filename : Inputs) {
    auto ReaderOrErr =
        SampleProfileReader::create(Filename, getGlobalContext());
    if (std::error_code EC = ReaderOrErr.getError())
      exitWithError(EC.message(), Filename);


    Readers.push_back(std::move(ReaderOrErr.get()));
    const auto Reader = Readers.back().get();
    if (std::error_code EC = Reader->read())
      exitWithError(EC.message(), Filename);

    StringMap<FunctionSamples> &Profiles = Reader->getProfiles();
    for (StringMap<FunctionSamples>::iterator I = Profiles.begin(),
                                              E = Profiles.end();
         I != E; ++I) {
      StringRef FName = I->first();
      FunctionSamples &Samples = I->second;
      ProfileMap[FName].merge(Samples);
    }
  }
  Writer->write(ProfileMap);
}

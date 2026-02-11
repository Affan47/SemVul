Initialization(const std::vector<FactorType>	&
                               , const std::vector<FactorType>			&
                               , const FactorMask							&
                               , size_t												nBestSize
                               , const std::string							&nBestFilePath)
{
  const StaticData &staticData = StaticData::Instance();


  m_surpressSingleBestOutput = false;

  if (nBestSize > 0) {
    if (nBestFilePath == "-" || nBestFilePath == "/dev/stdout") {
      m_nBestStream = &std::cout;
      m_surpressSingleBestOutput = true;
    } else {
      std::ofstream *file = new std::ofstream;
      m_nBestStream = file;
      file->open(nBestFilePath.c_str());
    }
  }


  if (staticData.GetOutputWordGraph()) {
    string fileName = staticData.GetParam("output-word-graph")[0];
    std::ofstream *file = new std::ofstream;
    m_outputWordGraphStream  = file;
    file->open(fileName.c_str());
  }


  if (staticData.GetOutputSearchGraph()) {
    string fileName;
    if (staticData.GetOutputSearchGraphExtended())
      fileName = staticData.GetParam("output-search-graph-extended")[0];
    else
      fileName = staticData.GetParam("output-search-graph")[0];
    std::ofstream *file = new std::ofstream;
    m_outputSearchGraphStream = file;
    file->open(fileName.c_str());
  }


  if (staticData.IsDetailedTranslationReportingEnabled()) {
    const std::string &path = staticData.GetDetailedTranslationReportingFilePath();
    m_detailedTranslationReportingStream = new std::ofstream(path.c_str());
    CHECK(m_detailedTranslationReportingStream->good());
  }


  if (! staticData.GetAlignmentOutputFile().empty()) {
    m_alignmentOutputStream = new ofstream(staticData.GetAlignmentOutputFile().c_str());
    CHECK(m_alignmentOutputStream->good());
  }

}

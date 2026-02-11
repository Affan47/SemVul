makeFOTBuilder(const FOTBuilder::Extension *&exts)
{
  if (outputFilename_.size() == 0) {
    if (defaultOutputBasename_.size() != 0) {
#ifdef SP_WIDE_SYSTEM
      outputFilename_ = defaultOutputBasename_;
#else
      outputFilename_ = codingSystem()->convertOut(defaultOutputBasename_);

      outputFilename_.resize(outputFilename_.size() - 1);
#endif
    }
    else
      outputFilename_.assign(SP_T("jade-out"), 8);
    outputFilename_ += SP_T('.');
    const AppChar *ext = outputTypeNames[outputType_];
    outputFilename_.append(ext, tcslen(ext));
  }
  switch (outputType_) {
#ifdef JADE_HTML
  case htmlType:
#endif
  case sgmlType:
  case xmlType:
    break;
  default:
    outputFilename_ += 0;
    if (!outputFile_.open(outputFilename_.data())) {
      message(JadeMessages::cannotOpenOutputError,
	      StringMessageArg(CmdLineApp::convertInput(outputFilename_.data())),
	      ErrnoMessageArg(errno));
      return 0;
    }
    break;
  }
  switch (outputType_) {
  case rtfType:
    unitsPerInch_ = 20*72;
    return makeRtfFOTBuilder(&outputFile_, outputOptions_, entityManager(), systemCharset(), this, exts);
  case texType:
    return makeTeXFOTBuilder(&outputFile_, this, exts);
#ifdef JADE_HTML
  case htmlType:
    return makeHtmlFOTBuilder(outputFilename_, this, exts);
#endif
#ifdef JADE_MIF
  case mifType:
    return makeMifFOTBuilder(outputFilename_, entityManager(), systemCharset(), this, exts);
#endif
  case fotType:
    return makeSgmlFOTBuilder(new RecordOutputCharStream(new EncodeOutputCharStream(&outputFile_,
						         outputCodingSystem_)));
  case sgmlType:
  case xmlType:
    return makeTransformFOTBuilder(this, outputType_ == xmlType, exts);
  default:
    break;
  }
  CANNOT_HAPPEN();
  return 0;
}

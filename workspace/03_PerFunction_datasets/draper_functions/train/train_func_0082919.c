ParseExecutablesAttribute(JobDescription& j) {
    std::map<std::string, std::string>::iterator itExecsAtt = j.OtherAttributes.find("nordugrid:xrsl;executables");
    if (itExecsAtt == j.OtherAttributes.end()) {
      return true;
    }

    RSLParser rp("&(executables = " + itExecsAtt->second + ")");
    const RSL* rexecs = rp.Parse(false);
    const RSLBoolean* bexecs;
    const RSLCondition* cexecs;
    std::list<std::string> execs;

    if (rexecs == NULL ||
        (bexecs = dynamic_cast<const RSLBoolean*>(rexecs)) == NULL ||
        (cexecs = dynamic_cast<const RSLCondition*>(*bexecs->begin())) == NULL ||
        !ListValue(cexecs, execs)) {

      logger.msg(DEBUG, "Error parsing the internally set executables attribute.");
      return false;
    }

    for (std::list<std::string>::const_iterator itExecs = execs.begin();
         itExecs != execs.end(); itExecs++) {
      bool fileExists = false;
      for (std::list<InputFileType>::iterator itFile = j.DataStaging.InputFiles.begin(); itFile != j.DataStaging.InputFiles.end(); itFile++) {
        if (itFile->Name == (*itExecs)) {
          itFile->IsExecutable = true;
          fileExists = true;
        }
      }

      if (!fileExists) {
        logger.msg(INFO, "File \"%s\" in the executables attribute is not present in the inputfiles attribute", *itExecs);
        return false;
      }
    }


    j.OtherAttributes.erase(itExecsAtt);

    return true;
  }

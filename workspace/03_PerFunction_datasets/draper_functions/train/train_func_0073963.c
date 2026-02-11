analyseFile(std::istream &fin, const std::string &filename)
{

    Preprocessor preprocessor(&_settings, this);
    std::list<std::string> configurations;
    std::string filedata = "";
    preprocessor.preprocess(fin, filedata, configurations, filename, _settings._includePaths);
    const std::string code = preprocessor.getcode(filedata, "", filename);

    if (_settings.checkConfiguration) {
        return;
    }


    Tokenizer tokenizer(&_settings, this);
    std::istringstream istr(code);
    tokenizer.tokenize(istr, filename.c_str(), "");
    tokenizer.simplifyTokenList2();


    std::set<std::string> data;
    for (std::list<Check *>::const_iterator it = Check::instances().begin(); it != Check::instances().end(); ++it) {
        (*it)->analyse(tokenizer.tokens(), data);
    }


    for (std::list<Check *>::const_iterator it = Check::instances().begin(); it != Check::instances().end(); ++it) {
        (*it)->saveAnalysisData(data);
    }
}

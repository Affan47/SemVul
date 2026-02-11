preprocess(std::istream &srcCodeStream, std::string &processedFile, std::list<std::string> &resultConfigurations, const std::string &filename, const std::list<std::string> &includePaths)
{
    if (file0.empty())
        file0 = filename;

    processedFile = read(srcCodeStream, filename);


    removeAsm(processedFile);


    {
        std::istringstream istr(processedFile);
        std::ostringstream ostr;
        std::string line;
        while (std::getline(istr, line)) {
            if (line.compare(0, 4, "#if ") == 0 || line.compare(0, 6, "#elif ") == 0) {
                std::string::size_type pos = 0;
                while ((pos = line.find(" defined ")) != std::string::npos) {
                    line[pos+8] = '(';
                    pos = line.find_first_of(" |&", pos + 8);
                    if (pos == std::string::npos)
                        line += ")";
                    else
                        line.insert(pos, ")");
                }
            }
            ostr << line << "\n";
        }
        processedFile = ostr.str();
    }

    if (_settings && !_settings->userDefines.empty()) {
        std::map<std::string, std::string> defs;


        std::string::size_type pos1 = 0;
        while (pos1 != std::string::npos) {
            const std::string::size_type pos2 = _settings->userDefines.find_first_of(";=", pos1);
            const std::string::size_type pos3 = _settings->userDefines.find(";", pos1);

            std::string name, value;
            if (pos2 == std::string::npos)
                name = _settings->userDefines.substr(pos1);
            else
                name = _settings->userDefines.substr(pos1, pos2 - pos1);
            if (pos2 != pos3) {
                if (pos3 == std::string::npos)
                    value = _settings->userDefines.substr(pos2+1);
                else
                    value = _settings->userDefines.substr(pos2+1, pos3 - pos2 - 1);
            }

            defs[name] = value;

            pos1 = pos3;
            if (pos1 != std::string::npos)
                pos1++;
        }

        processedFile = handleIncludes(processedFile, filename, includePaths, defs);
        if (_settings->userDefines.empty())
            resultConfigurations = getcfgs(processedFile, filename);

    } else {

        handleIncludes(processedFile, filename, includePaths);

        processedFile = replaceIfDefined(processedFile);


        resultConfigurations = getcfgs(processedFile, filename);


        handleUndef(resultConfigurations);
    }
}

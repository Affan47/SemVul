preprocess(std::istream &srcCodeStream, std::string &processedFile, std::list<std::string> &resultConfigurations, const std::string &filename, const std::list<std::string> &includePaths)
{
    if (file0.empty())
        file0 = filename;

    processedFile = read(srcCodeStream, filename, _settings);


    preprocessWhitespaces(processedFile);


    removeAsm(processedFile);


    {
        std::istringstream istr(processedFile.c_str());
        std::ostringstream ostr;
        std::string line;
        while (std::getline(istr, line))
        {
            if (line.compare(0, 4, "#if ") == 0 || line.compare(0, 6, "#elif ") == 0)
            {
                std::string::size_type pos = 0;
                while ((pos = line.find(" defined ")) != std::string::npos)
                {
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

    std::set<std::string> systemIncludes;
    handleIncludes(processedFile, filename, includePaths, systemIncludes);

    processedFile = replaceIfDefined(processedFile);


    if (!_settings || (_settings && _settings->userDefines.empty()))
        resultConfigurations = getcfgs(processedFile, filename);
}

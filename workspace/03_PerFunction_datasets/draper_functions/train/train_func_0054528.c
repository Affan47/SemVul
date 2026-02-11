parseCmdFiles(ModifyCmds& modifyCmds,
                       const Params::CmdFiles& cmdFiles)
    {
        Params::CmdFiles::const_iterator end = cmdFiles.end();
        Params::CmdFiles::const_iterator filename = cmdFiles.begin();
        for ( ; filename != end; ++filename) {
            try {
                std::ifstream file(filename->c_str());
                if (!file) {
                    std::cerr << *filename << ": "
                              << _("Failed to open command file for reading\n");
                    return false;
                }
                int num = 0;
                std::string line;
                while (std::getline(file, line)) {
                    ModifyCmd modifyCmd;
                    if (parseLine(modifyCmd, line, ++num)) {
                        modifyCmds.push_back(modifyCmd);
                    }
                }
            }
            catch (const Exiv2::AnyError& error) {
                std::cerr << *filename << ", " << _("line") << " " << error << "\n";
                return false;
            }
        }
        return true;
    }

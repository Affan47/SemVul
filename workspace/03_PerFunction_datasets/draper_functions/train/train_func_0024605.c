findCommandLineOpts(int numargs, char** argv, UnaryOptionList& unaryOptList,
        BinaryOptionList& binOptList)
    {
        int startIndex = 1;
        for (int i = 1; i < numargs; ++i)
        {
            String tmp(argv[i]);
            if (StringUtil::startsWith(tmp, "-"))
            {
                UnaryOptionList::iterator ui = unaryOptList.find(argv[i]);
                if(ui != unaryOptList.end())
                {
                    ui->second = true;
                    ++startIndex;
                    continue;
                }
                BinaryOptionList::iterator bi = binOptList.find(argv[i]);
                if(bi != binOptList.end())
                {
                    bi->second = argv[i+1];
                    startIndex += 2;
                    ++i;
                    continue;
                }


                LogManager::getSingleton().logMessage("Invalid option " + tmp, LML_CRITICAL);

            }
        }
        return startIndex;
    }

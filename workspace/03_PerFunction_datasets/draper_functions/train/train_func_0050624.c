invokeParser(String& line, AttribParserList& parsers)
    {

        StringVector splitCmd(StringUtil::split(line, " \t", 1));


        AttribParserList::iterator iparser = parsers.find(splitCmd[0]);
        if (iparser == parsers.end())
        {

            logParseError("Unrecognised command: " + splitCmd[0], mScriptContext);
            return false;
        }
        else
        {
            String cmd;
            if(splitCmd.size() >= 2)
                cmd = splitCmd[1];

            return iparser->second( cmd, mScriptContext );
        }
    }

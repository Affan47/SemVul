parseConfigFile(string cfgFile)
{
    #ifndef MOD_CLNT_EMBEDDED_CFG


    ifstream f;
    f.open(cfgFile.c_str());
    if ( ! f.is_open()  ) {
        Log(Crit) << "Unable to open " << cfgFile << " file." << LogEnd;
            return false;
    } else {
        Log(Notice) << "Parsing " << cfgFile << " config file..." << LogEnd;
    }
    yyFlexLexer lexer(&f,&clog);
    ClntParser parser(&lexer);
    parser.CfgMgr = this;
    int result = parser.yyparse();
    Log(Debug) << "Parsing " << cfgFile << " done, result=" << result << LogEnd;
    f.close();

    if (result) {

        Log(Crit) << "Fatal error during config parsing." << LogEnd;
        this->DUID=new TDUID();
        return false;
    }

    if (!setGlobalOptions(&parser)) {
        return false;
    }


    if (!matchParsedSystemInterfaces(&parser)) {
        return false;
    }
#else


    HardcodedCfgFunc *cfgMaker = &HardcodedCfgExample;


    cfgMaker(this, cfgFile);

#endif


    if(!validateConfig()) {
        return false;
    }

    return true;
}

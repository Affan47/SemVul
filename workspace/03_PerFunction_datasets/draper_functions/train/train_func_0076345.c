dump()
{

    cerr << endl << "Dump RcInitFile:" << endl;
    cerr << "\tTimer interupt delay value: " << _delay << endl;
    cerr << "\tFlash debugger: "
         << ((_debugger)?"enabled":"disabled") << endl;
    cerr << "\tVerbosity Level: " << _verbosity << endl;
    cerr << "\tDump ActionScript processing: "
         << ((_actionDump)?"enabled":"disabled") << endl;
    cerr << "\tDump parser info: "
         << ((_parserDump)?"enabled":"disabled") << endl;
    cerr << "\tActionScript coding errors verbosity: "
         << ((_verboseASCodingErrors)?"enabled":"disabled") << endl;
    cerr << "\tMalformed SWF verbosity: "
         << ((_verboseASCodingErrors)?"enabled":"disabled") << endl;
    cerr << "\tUse Splash Screen: "
         << ((_splashScreen)?"enabled":"disabled") << endl;
    cerr << "\tUse Local Domain Only: "
         << ((_localdomainOnly)?"enabled":"disabled") << endl;
    cerr << "\tUse Localhost Only: "
         << ((_localhostOnly)?"enabled":"disabled") << endl;
    cerr << "\tWrite Debug Log To Disk: "
         << ((_writeLog)?"enabled":"disabled") << endl;
    cerr << "\tAllow insecure SSL connections: "
         << ((_insecureSSL)?"yes":"no") << endl;
    cerr << "\tEnable sound: "
         << ((_sound)?"enabled":"disabled") << endl;
    cerr << "\tEnable Plugin sound: "
         << ((_pluginSound)?"enabled":"disabled") << endl;
    cerr << "\tEnable Extensions: "
         << ((_extensionsEnabled)?"enabled":"disabled") << endl;

    if (!_log.empty()) {
        cerr << "\tDebug Log name is: " << _log << endl;
    }

    if (!_flashVersionString.empty()) {
        cerr << "\tFlash Version String is: " << _flashVersionString << endl;
    }

    if(!_gstaudiosink.empty()) {
        cerr << "\tGST Audio Sink is: " << _gstaudiosink << endl;
    }

    cerr << "\tWhitelist: ";
    writeList (_whitelist, cerr);

    cerr << "\tBlacklist: ";
    writeList (_blacklist, cerr);

    cerr << "\tSandbox: ";
    writeList (_localSandboxPath, cerr);
}

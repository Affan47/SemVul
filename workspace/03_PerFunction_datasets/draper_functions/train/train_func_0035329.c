parseCommandLine(OFCommandLine &cmd,
                                              int argCount,
                                              char *argValue[],
                                              const int flags,
                                              const int startPos)
{
    CmdLine = &cmd;
    OFCommandLine::E_ParseStatus status = cmd.parseLine(argCount, argValue, flags, startPos);
    OFBool result = OFFalse;
    switch (status)
    {
        case OFCommandLine::PS_NoArguments:

            if (cmd.getMinParamCount() > 0)
                printUsage();
            else
                result = OFTrue;
            break;
        case OFCommandLine::PS_ExclusiveOption:

            if (cmd.findOption("--help"))
                printUsage();
            else
                result = OFTrue;
            break;
        case OFCommandLine::PS_Normal:
            result = OFTrue;
            break;
        default:
            {
                OFString str;
                cmd.getStatusString(status, str);
                printError(str.c_str());
            }
            break;
    }
    return result;
}

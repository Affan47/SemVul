main(int argc, char *argv[])
{
    OFConsoleApplication app(OFFIS_CONSOLE_APPLICATION , "Test if file uses DICOM part 10 format", rcsid);
    OFCommandLine cmd;


    cmd.addParam("file", OFCmdParam::PM_MultiMandatory);
    app.parseCommandLine(cmd, argc, argv, OFCommandLine::PF_ExpandWildcards);

    int badCount = 0;
    int count = cmd.getParamCount();
    const char *fname = NULL;
    for (int i=1; i<=count; i++) {
        cmd.getParam(i, fname);
        OFBool ok = OFFalse;
        FILE* f = NULL;

        if (fname && (strlen(fname) > 0)) f = fopen(fname, "rb");
        if (f == 0) {
            ok = OFFalse;
        } else {
            char signature[4];
            if ((fseek(f, DCM_PreambleLen, SEEK_SET) < 0) ||
                (fread(signature, 1, DCM_MagicLen, f) != DCM_MagicLen)) {
                ok = OFFalse;
            } else if (strncmp(signature, DCM_Magic, DCM_MagicLen) != 0) {
                ok = OFFalse;
            } else {

                ok = OFTrue;
            }
            fclose(f);
        }
        if (ok) {
            COUT << "yes: " << fname << OFendl;
        } else {
            COUT << "no: " << fname << OFendl;
            badCount++;
        }
    }


    return badCount;
}

findDesktop(char *argv[]) {


    switch (LoadDesktopMode) {
    default:


        if (FileExists(DESKTOP_NAME))
            ExpandPath(DESKTOP_NAME, DesktopFileName, sizeof(DesktopFileName));
        else {

#ifdef UNIX
            ExpandPath("~/" DESKTOP_NAME, DesktopFileName, sizeof(DesktopFileName));
#else
            JustDirectory(argv[0], DesktopFileName, sizeof(DesktopFileName));
            strlcat(DesktopFileName, DESKTOP_NAME, sizeof(DesktopFileName));
#endif
        }
        return FileExists(DesktopFileName);

    case 1:
    case 2:

        ExpandPath(".", DesktopFileName, sizeof(DesktopFileName));


        for (;;) {

            char *pe = DesktopFileName + strlen(DesktopFileName);
            Slash(DesktopFileName, 1);
            strlcat(DesktopFileName, DESKTOP_NAME, sizeof(DesktopFileName));


            if (FileExists(DesktopFileName)) {

                return 1;
            }


            *pe = 0;


            char *p = SepRChr(DesktopFileName);

            if (p == NULL) {

                ExpandPath(".", DesktopFileName, sizeof(DesktopFileName));
                Slash(DesktopFileName, 1);
                strlcat(DesktopFileName, DESKTOP_NAME, sizeof(DesktopFileName));

                SaveDesktopOnExit = 0;
                return 0;
            }
            *p = 0;
        }
    }
}

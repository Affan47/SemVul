showInfo(ostream &ostr) {
    _FB_USES_NLS;
    ostr <<
        _FB_CONSOLETEXT(Common, FluxboxVersion, "Fluxbox version", "Fluxbox version heading")
        << ": "
        << __fluxbox_version <<endl;

    if (strlen(gitrevision()) > 0)
        ostr << _FB_CONSOLETEXT(Common, SvnRevision, "GIT Revision", "Revision number in GIT repositary")
            << ": "
            << gitrevision() << endl;
#if defined(__DATE__) && defined(__TIME__)
    ostr << _FB_CONSOLETEXT(Common, Compiled, "Compiled", "Time fluxbox was compiled")
        << ": "
        << __DATE__
        << " "
        << __TIME__ << endl;
#endif
#ifdef __fluxbox_compiler
    ostr << _FB_CONSOLETEXT(Common, Compiler, "Compiler", "Compiler used to build fluxbox")
        << ": "
        << __fluxbox_compiler << endl;
#endif
#ifdef __fluxbox_compiler_version
    ostr << _FB_CONSOLETEXT(Common, CompilerVersion, "Compiler version", "Compiler version used to build fluxbox")
        << ": "
        << __fluxbox_compiler_version << endl;
#endif

    ostr << endl
        <<_FB_CONSOLETEXT(Common, Defaults, "Defaults", "Default values compiled in")
        << ": " << endl;

    ostr <<_FB_CONSOLETEXT(Common, DefaultMenuFile, "    menu", "default menu file (right aligned - make sure same width as other default values)")
        << ": "
        << FbTk::StringUtil::expandFilename(DEFAULTMENU) << endl;
    ostr << _FB_CONSOLETEXT(Common, DefaultStyle, "   style", "default style (right aligned - make sure same width as other default values)")
        << ": "
        << FbTk::StringUtil::expandFilename(DEFAULTSTYLE) << endl;

    ostr << _FB_CONSOLETEXT(Common, DefaultKeyFile, "    keys", "default key file (right aligned - make sure same width as other default values)")
        << ": "
        << FbTk::StringUtil::expandFilename(DEFAULTKEYSFILE) << endl;
    ostr << _FB_CONSOLETEXT(Common, DefaultInitFile, "    init", "default init file (right aligned - make sure same width as other default values)")
        << ": "
        << FbTk::StringUtil::expandFilename(DEFAULT_INITFILE) << endl;

#ifdef NLS
    ostr << _FB_CONSOLETEXT(Common, DefaultLocalePath, "    nls", "location for localization files (right aligned - make sure same width as other default values)")
        << ": "
        << FbTk::StringUtil::expandFilename(LOCALEPATH) << endl;
#endif

    const char NOT[] = "-";
    ostr << endl
        << _FB_CONSOLETEXT(Common, CompiledOptions, "Compiled options", "Options used when compiled")
        << " (" << NOT << " => "
        << _FB_CONSOLETEXT(Common, Disabled, "disabled", "option is turned off") << "): " << endl
        <<


#ifndef HAVE_FRIBIDI
        NOT <<
#endif
        "BIDI" << endl <<

#ifndef DEBUG
        NOT <<
#endif
        "DEBUG" << endl <<

#ifndef USE_EWMH
        NOT <<
#endif
        "EWMH" << endl <<

#ifndef HAVE_IMLIB2
        NOT<<
#endif
        "IMLIB2" << endl <<

#ifndef NLS
        NOT<<
#endif
        "NLS" << endl <<

#ifndef REMEMBER
        NOT <<
#endif
        "REMEMBER" << endl <<

#ifndef HAVE_XRENDER
        NOT <<
#endif
        "RENDER" << endl <<

#ifndef SHAPE
        NOT <<
#endif
        "SHAPE" << endl <<

#ifndef USE_SLIT
        NOT <<
#endif
        "SLIT" << endl <<

#ifndef USE_SYSTRAY
        NOT <<
#endif
        "SYSTEMTRAY" << endl <<


#ifndef USE_TOOLBAR
        NOT <<
#endif
        "TOOLBAR" << endl <<

#ifndef HAVE_RANDR
        NOT <<
#endif
        "RANDR" <<
#ifdef HAVE_RANDR1_2
        "1.2" <<
#endif
        endl <<

#ifndef USE_XFT
        NOT <<
#endif
        "XFT" << endl <<

#ifndef XINERAMA
        NOT <<
#endif
        "XINERAMA" << endl <<

#ifndef USE_XMB
        NOT <<
#endif
        "XMB" << endl <<

#ifndef HAVE_XPM
        NOT <<
#endif
        "XPM" << endl

        << endl;
}

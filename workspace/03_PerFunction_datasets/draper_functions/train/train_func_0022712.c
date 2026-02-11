DetermineExecutablePath()
    {
        #ifdef __WXMSW__
            wxChar name[MAX_PATH];
            GetModuleFileName(0L, name, MAX_PATH);
            wxFileName fname(name);
            return fname.GetPath(wxPATH_GET_VOLUME);
        #else
        #ifdef __linux__
            char c[PATH_MAX+1];
            char *p = realpath("/proc/self/exe", &c[0]);
            if (p == nullptr)
                return _T(".");
            wxFileName fname(cbC2U(p));
            return fname.GetPath(wxPATH_GET_VOLUME);
        #elif defined(sun) || defined(__sun)
            wxFileName fname(cbC2U(getexecname()));
            return fname.GetPath(wxPATH_GET_VOLUME);
        #elif defined(__APPLE__) && defined(__MACH__)
            char path[MAXPATHLEN+1];
            uint32_t path_len = MAXPATHLEN;

            _NSGetExecutablePath(path, &path_len);
            wxFileName fname(wxString(path, wxConvUTF8));
            return fname.GetPath(wxPATH_GET_VOLUME);
        #else
            return _T(".");
        #endif
        #endif
    }

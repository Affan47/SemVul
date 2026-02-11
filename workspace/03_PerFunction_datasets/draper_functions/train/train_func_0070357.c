update_window_patterns_for_iconbar(FbTk::ResourceManager& rm,
        const FbTk::FbString& keyfilename, const FbTk::FbString& appsfilename) {


    FbTk::Resource<string> *rc_mode =
        new FbTk::Resource<string>(rm, "Workspace",
                                   "session.screen0.iconbar.mode",
                                   "Session.Screen0.Iconbar.Mode");

    std::string mode = FbTk::StringUtil::toLower(**rc_mode);
    if (mode == "none")
        *rc_mode = "none";
    else if (mode == "icons")
        *rc_mode = "{static groups} (minimized=yes)";
    else if (mode == "noicons")
        *rc_mode = "{static groups} (minimized=no)";
    else if (mode == "workspaceicons")
        *rc_mode = "{static groups} (minimized=yes) (workspace)";
    else if (mode == "workspacenoicons")
        *rc_mode = "{static groups} (minimized=no) (workspace)";
    else if (mode == "allwindows")
        *rc_mode = "{static groups}";
    else
        *rc_mode = "{static groups} (workspace)";

}

SDLAppInit(std::string apptitle, std::string execname) {
    gSDLAppTitle = apptitle;
    gSDLAppExec  = execname;

    std::string conf_dir     = "";
    std::string resource_dir = "data/";
    std::string fonts_dir    = "data/fonts/";
    std::string shaders_dir  = "data/shaders/";
#ifdef _WIN32

    char szAppPath[MAX_PATH];
    GetModuleFileName(0, szAppPath, MAX_PATH);


    std::string exepath = std::string(szAppPath);

    int pos = exepath.rfind("\\");

    std::string path = exepath.substr(0, pos+1);
    conf_dir     = path + std::string("\\");
    resource_dir = path + std::string("\\data\\");
    fonts_dir    = path + std::string("\\data\\fonts\\");
    shaders_dir  = path + std::string("\\data\\shaders\\");
#else

    char cwd_buff[1024];

    if(getcwd(cwd_buff, 1024) == cwd_buff) {
        conf_dir     = std::string(cwd_buff) + std::string("/");
        resource_dir = std::string(cwd_buff) + std::string("/") + resource_dir;
        fonts_dir    = std::string(cwd_buff) + std::string("/") + fonts_dir;
        shaders_dir  = std::string(cwd_buff) + std::string("/") + shaders_dir;
    }

#endif

#ifdef SDLAPP_CONF_DIR
    if (SDLAppDirExists(SDLAPP_CONF_DIR)) {
        conf_dir = SDLAPP_CONF_DIR;
    }
#endif

#ifdef SDLAPP_RESOURCE_DIR
    if (SDLAppDirExists(SDLAPP_RESOURCE_DIR)) {
        resource_dir = SDLAPP_RESOURCE_DIR;
        fonts_dir    = SDLAPP_RESOURCE_DIR + std::string("/fonts/");
        shaders_dir  = SDLAPP_RESOURCE_DIR + std::string("/shaders/");
    }
#endif

#ifdef SDLAPP_FONT_DIR
    if (SDLAppDirExists(SDLAPP_FONT_DIR)) {
        fonts_dir    = SDLAPP_FONT_DIR;
    }
#endif

    resource_dir  = SDLAppAddSlash(resource_dir);
    conf_dir      = SDLAppAddSlash(conf_dir);
    fonts_dir     = SDLAppAddSlash(fonts_dir);
    shaders_dir   = SDLAppAddSlash(shaders_dir);

    texturemanager.setDir(resource_dir);
    fontmanager.setDir(fonts_dir);
    shadermanager.setDir(shaders_dir);

    gSDLAppResourceDir = resource_dir;
    gSDLAppConfDir     = conf_dir;
    gSDLAppShaderDir   = shaders_dir;

    fontmanager.init();
}

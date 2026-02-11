setupExtensions() {

    GLenum err = glewInit();

    if (GLEW_OK != err) {

        char glewerr[1024];
        snprintf(glewerr, 1024, "GLEW Error: %s", glewGetErrorString(err));

        throw SDLInitException(std::string(glewerr));
    }
}

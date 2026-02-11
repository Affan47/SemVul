sendGeneratedImage(_WebClientConnection* cc, char *path)
{
    INFO2("[WS]: sendGeneratedImage %s", path);

    const char* home = getenv("HOME");
    if (!home) {
        return;
    }

    struct stat statbuf;

    string_t* img = stringNew(home);
    stringAppend(img,"/.anyRemote/");
    stringAppend(img,path);

    INFO2("[WS]: sendGeneratedImage full name %s", img->str);

    if (stat(img->str, &statbuf) >= 0) {
        sendFile(cc, img->str, &statbuf);
    } else {
        sendError(cc, 404, "Not Found", NULL, "File not found.");
    }
    stringFree(img, BOOL_YES);
}

parseScreenDef(char* buffer)
{


    int gap = strlen("x-CiscoIPPhoneDisplay: ");
    if (!buffer || strlen(buffer) < gap) {
        return;
    }

    char* start = buffer+gap;
    char* scrDef = strdup(start);

    char* w = strtok(scrDef, ",");
    char* h = strtok(NULL,   ",");

    strtok(NULL,   ",");
    char* g = strtok(NULL,   ",");

    int sW      = atoi(w);
    int sH      = atoi(h);


    boolean_t sG = (g && g[0] == 'G');

    if (_xmlLayoutOk &&
            (_xmlScreenW != sW ||
             _xmlScreenH != sH ||
             _xmlScreenG != sG)) {

        _xmlLayoutOk = BOOL_NO;
    }

    _xmlScreenW = sW;
    _xmlScreenH = sH;
    _xmlScreenG = sG;

    free(scrDef);
}

setMenu()
{
    char *token = strtok(NULL,",");
    if (!token) {
        return;
    }
    while (isspace(*token)) {
        ++token;
    }

    if (strncmp(token,"add",3) == 0 || strncmp(token,"replace",7) == 0) {

        logger(L_INF, "[DS]: setMenu add/replace");

        if (strcmp(token,"replace") == 0) {
            setupDefMenu();
        }

        char *token3 = strtok(NULL,",");
        while (token3) {

            while (isspace(*token3)) {
                ++token3;
            }

            INFO2("[DS]: Set(menu, ...) %s", token3);

            mutexLock(M_STATE);

            string_t* dup = stringNew(token3);
            _userMenu = listSingleAppend(_userMenu, dup);
            token3 = strtok(NULL,",");

            mutexUnlock(M_STATE);
        }
    } else if (strncmp(token,"clear",5) == 0) {
        mutexLock(M_STATE);
        freeMenu();
        mutexUnlock(M_STATE);
    } else {
        ERROR2("[DS]: Can to parse Set(menu, ...)");
    }
}

setText(boolean_t split)
{

    boolean_t setupMenu = (_curForm != TX);

    char *token = strtok(NULL,",");
    if (!token) {
        return;
    }
    while (isspace(*token)) {
        ++token;
    }


    if (strncmp(token,"add",3) == 0 || strncmp(token,"replace",7) == 0) {

        mutexLock(M_STATE);
        _curForm = TX;

        char *token2 = strtok(NULL,",");
        if (!token2) {
            return;
        }


        if (strncmp(token,"replace",7) == 0) {
            resetTfText();
        }

        if (strcmp(token2,"SAME") != 0) {
	        setTfCaption(token2);
        }

	    if (split) {
            char *token3 = strtok(NULL,"\n");
            while (token3) {


		        addTfText(token3);
        	    token3 = strtok(NULL,"\n");
            }
	    } else {
	        addTfText(token2 + strlen(token2) + 1);
	    }
        mutexUnlock(M_STATE);

    } else if (strcmp(token,"close") == 0) {

        char *token2 = strtok(NULL,",");
        if (token2 && strcmp(token,"clear") == 0) {
            mutexLock(M_STATE);
            resetTfText();
            mutexUnlock(M_STATE);
        }

        _curForm = CF;
        setupDefMenu();
        return;

    } else if (strncmp(token,"clear",5) == 0) {
        mutexLock(M_STATE);
        resetTfText();
        mutexUnlock(M_STATE);
        return;
    } else if (strncmp(token,"fg",2) == 0) {
        mutexLock(M_STATE);
        setFgBg(TX,BOOL_YES);
        mutexUnlock(M_STATE);
        return;
    } else if (strncmp(token,"bg",2) == 0) {
        mutexLock(M_STATE);
        setFgBg(TX,BOOL_NO);
        mutexUnlock(M_STATE);
        return;
    } else if (strncmp(token,"font",4) == 0) {
        mutexLock(M_STATE);
        setFont(TX);
        mutexUnlock(M_STATE);
        return;
    } else if (strncmp(token,"show",4) == 0) {
        _curForm = TX;
    } else {
        ERROR2("[DS]: Can to parse Set(text, ...)");
        return;
    }

    if (setupMenu) {
        setupDefMenu();
    }
}

pkix_pl_InfoAccess_ParseTokens(
        PLArenaPool *arena,
        char **startPos,
        char ***tokens,
        char separator,
        char terminator,
        void *plContext)
{
        PKIX_UInt32 numFilters = 0;
        char *endPos = NULL;
        char **filterP = NULL;

        PKIX_ENTER(INFOACCESS, "pkix_pl_InfoAccess_ParseTokens");
        PKIX_NULLCHECK_THREE(arena, startPos, tokens);

        endPos = *startPos;


        numFilters = 0;
        while (*endPos != terminator && *endPos != '\0') {
                endPos++;
                if (*endPos == separator) {
                        numFilters++;
                }
        }

        if (*endPos != terminator) {
                PKIX_ERROR(PKIX_LOCATIONSTRINGNOTPROPERLYTERMINATED);
        }


        if (endPos > *startPos && *(endPos-1) != separator) {
                numFilters++;
        }


        if (numFilters > 2) numFilters = 2;

        filterP = PORT_ArenaZNewArray(arena, char*, numFilters+1);
        if (filterP == NULL) {
            PKIX_ERROR(PKIX_PORTARENAALLOCFAILED);
        }


        *tokens = filterP;
        endPos = *startPos;

        while (numFilters) {
            if (*endPos == separator || *endPos == terminator) {
                    PKIX_UInt32 len = endPos - *startPos;
                    char *p = PORT_ArenaZAlloc(arena, len+1);
                    if (p == NULL) {
                        PKIX_ERROR(PKIX_PORTARENAALLOCFAILED);
                    }

                    PORT_Memcpy(p, *startPos, len);
                    p[len] = '\0';

                    *filterP = p;
                    filterP++;
                    numFilters--;

                    separator = terminator;

                    if (*endPos == '\0') {
                        *startPos = endPos;
                        break;
                    } else {
                        endPos++;
                        *startPos = endPos;
                        continue;
                    }
            }
            endPos++;
        }

        *filterP = NULL;

cleanup:

        PKIX_RETURN(INFOACCESS);
}

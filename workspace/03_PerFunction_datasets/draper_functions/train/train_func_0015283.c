xml_escape_the_string(const char *str, int slen)
{
    size_t      extra;
    size_t      len;
    size_t      i;
    const char *cp;
    char       *ncp;
    char       *rcp;

    if (!str)
        return NULL;

    cp = str;

    if (slen < 0)
        len = HDstrlen(str);
    else
        len = slen;

    extra = 0;

    for (i = 0; i < len; i++) {
        if (*cp == '\\') {
            extra++;
        }
        else if (*cp == '\"') {
            extra++;
        }
        else if (*cp == '\'') {
            extra += (HDstrlen(apos) - 1);
        }
        else if (*cp == '<') {
            extra += (HDstrlen(lt) - 1);
        }
        else if (*cp == '>') {
            extra += (HDstrlen(gt) - 1);
        }
        else if (*cp == '&') {
            extra += (HDstrlen(amp) - 1);
        }
        cp++;
    }

    cp = str;
    rcp = ncp = (char *) HDcalloc((len + extra + 1), sizeof(char));

    if (ncp == NULL)
        return NULL;

    for (i = 0; i < len; i++) {
        if (*cp == '\\') {
            *ncp++ = '\\';
            *ncp++ = *cp++;
        }
        else if (*cp == '\"') {
            *ncp++ = '\\';
            *ncp++ = *cp++;
        }
        else if (*cp == '\'') {
            HDstrncpy(ncp, apos, HDstrlen(apos));
            ncp += HDstrlen(apos);
            cp++;
        }
        else if (*cp == '<') {
            HDstrncpy(ncp, lt, HDstrlen(lt));
            ncp += HDstrlen(lt);
            cp++;
        }
        else if (*cp == '>') {
            HDstrncpy(ncp, gt, HDstrlen(gt));
            ncp += HDstrlen(gt);
            cp++;
        }
        else if (*cp == '&') {
            HDstrncpy(ncp, amp, HDstrlen(amp));
            ncp += HDstrlen(amp);
            cp++;
        }
        else {
            *ncp++ = *cp++;
        }
    }

    *ncp = '\0';
    return rcp;
}

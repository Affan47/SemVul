find_bindir(char *erlpath)
{


    char *p;
    char *p2;
    char buffer[MAXPATHLEN];

    strcpy(buffer, erlpath);


    for (p = buffer+strlen(buffer)-1 ;p >= buffer && *p != DIRSEPCHAR; --p)
        ;
    *p = '\0';
    p--;


    for (;p >= buffer && *p != DIRSEPCHAR; --p)
        ;
    p--;
    for (p2 = p;p2 >= buffer && *p2 != DIRSEPCHAR; --p2)
        ;
    p2++;
    if (strncmp(p2, "erts-", 5) == 0) {
	p = strsave(buffer);
	return p;
    }


    *++p ='\0';

    p = find_erts_vsn(buffer);
    if (p == NULL) {
	return strsave(buffer);
    } else {
	return p;
    }
}

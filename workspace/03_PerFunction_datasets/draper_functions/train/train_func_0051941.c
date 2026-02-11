cyrus_acl_set(acl, identifier, mode, access, canonproc, canonrock)
char **acl;
const char *identifier;
int mode;
int access;
cyrus_acl_canonproc_t *canonproc;
void *canonrock;
{
    const char *canonid;
    char *newidentifier = 0;
    char *newacl;
    char *thisid, *nextid;
    int oldaccess = 0;
    char *rights;


    canonid = auth_canonifyid(*identifier == '-' ? identifier+1 : identifier, 0);
    if (canonid) {
	if (*identifier == '-') {
	    newidentifier = xmalloc(strlen(canonid)+2);
	    newidentifier[0] = '-';
	    strcpy(newidentifier+1, canonid);
	    identifier = newidentifier;
	} else {
	    identifier = canonid;
	}
    } else if (access != 0L) {
	return -1;
    } else {

    }


    for (thisid = nextid = *acl; *thisid; thisid = nextid) {
	rights = strchr(thisid, '\t');
	if (!rights) {

	    *thisid = '\0';
	    nextid = thisid;
	    break;
	}
	*rights++ = '\0';

	nextid = strchr(rights, '\t');
	if (!nextid) {

	    *thisid = '\0';
	    nextid = thisid;
	    break;
	}
	*nextid++ = '\0';

	if (strcmp(identifier, thisid) == 0) {
	    oldaccess = cyrus_acl_strtomask(rights);
	    break;
	}
	rights[-1] = '\t';
	nextid[-1] = '\t';
    }

    switch (mode) {
    case ACL_MODE_SET:
	break;

    case ACL_MODE_ADD:
	access |= oldaccess;
	break;

    case ACL_MODE_REMOVE:
	access = oldaccess & ~access;
	break;
    }

    if (canonproc) {
	if (*identifier == '-')
	    access = ~(canonproc(canonrock, identifier+1, ~access));
	else
	    access = canonproc(canonrock, identifier, access);
    }

    if (access == 0L) {

	strcpy(thisid, nextid);
    }
    else {

	newacl = xmalloc((thisid - *acl) + strlen(identifier) + 40 +
			 strlen(nextid));
	strncpy(newacl, *acl, (thisid - *acl));
	strcpy(newacl + (thisid - *acl), identifier);
	strcat(newacl, "\t");
	(void) cyrus_acl_masktostr(access, newacl + strlen(newacl));
	strcat(newacl, "\t");
	strcat(newacl, nextid);
	free(*acl);
	*acl = newacl;
    }

    if (newidentifier) free(newidentifier);
    return 0;
}

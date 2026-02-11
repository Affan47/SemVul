same_guid(NOTICE& n1, NOTICE& n2) {
    if (!strlen(n1.guid)) return false;
    return !strcmp(n1.guid, n2.guid);
}

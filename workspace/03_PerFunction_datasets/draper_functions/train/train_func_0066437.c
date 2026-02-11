getPassword(char *passBuf, int passLen)
{
    char    *password, *confirm;

    password = getpass("New password: ");
    strncpy(passBuf, password, passLen - 1);
    confirm = getpass("Confirm password: ");
    if (strcmp(passBuf, confirm) == 0) {
        return passBuf;
    }
    mprError("%s: Error: Password not verified", programName);
    return 0;
}

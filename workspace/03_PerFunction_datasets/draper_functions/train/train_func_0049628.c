httpValidateFileCredentials(HttpAuth *auth, cchar *realm, cchar *user, cchar *password, cchar *requiredPassword,
    char **msg)
{
    char    passbuf[HTTP_MAX_PASS * 2], *hashedPassword;

    hashedPassword = 0;

    if (auth->type == HTTP_AUTH_BASIC) {
        mprSprintf(passbuf, sizeof(passbuf), "%s:%s:%s", user, realm, password);
        hashedPassword = mprGetMD5(passbuf);
        password = hashedPassword;
    }
    if (!isUserValid(auth, realm, user)) {
        *msg = "Access Denied, Unknown User.";
        return 0;
    }
    if (strcmp(password, requiredPassword)) {
        *msg = "Access Denied, Wrong Password.";
        return 0;
    }
    return 1;
}

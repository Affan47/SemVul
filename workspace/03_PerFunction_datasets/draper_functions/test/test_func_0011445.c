CheckAuthorization(name_length, name, data_length, data)
unsigned short name_length;
char *name;
unsigned short data_length;
char *data;
{
    int i;

    if (ShouldLoadAuth) {
        if (!LoadAuthorization())
            EnableLocalHost();
    }
    if (name_length)
        for (i = 0; i < NUM_AUTHORIZATION; i++) {
            if (protocols[i].name_length == name_length &&
                bcmp(protocols[i].name, name, (int) name_length) == 0) {
                return (*protocols[i].Check) (data_length, data);
            }
        }
    return (AuID) ~ 0L;
}

GetInternalClientName(int ref)
{
    char name_res[JACK_CLIENT_NAME_SIZE + 1];
    int result = -1;
    fChannel->GetInternalClientName(GetClientControl()->fRefNum, ref, name_res, &result);
    return (result < 0) ? NULL : strdup(name_res);
}

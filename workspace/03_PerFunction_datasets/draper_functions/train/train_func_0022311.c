globus_hashtable_string_keyeq(
    void *                              string1,
    void *                              string2)
{
    if(string1 == string2 ||
        (string1 && string2 && strcmp(string1, string2) == 0))
    {
        return 1;
    }

    return 0;
}

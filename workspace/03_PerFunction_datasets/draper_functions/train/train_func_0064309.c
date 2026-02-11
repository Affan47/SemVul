env_str_equal_func(void *key1, void *key2)
{
    String str1;
    String str2;

    if(key1 == NULL || key2 == NULL)
	return false;

    str1 = key1;
    str2 = key2;

    if(wcscmp(str1, str2) == 0)
	return true;

    return false;
}

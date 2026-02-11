printDeviceList(const char *list)
{
    if(!list || *list == '\0')
        printf("    !!! none !!!\n");
    else do {
        printf("    %s\n", list);
        list += strlen(list) + 1;
    } while(*list != '\0');
}

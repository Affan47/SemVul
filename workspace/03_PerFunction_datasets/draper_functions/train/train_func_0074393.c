jfs_mkfs(cdico *d, char *partition, char *fsoptions)
{
    char command[2048];
    char buffer[2048];
    char options[2048];
    int exitst;


    if (exec_command(command, sizeof(command), NULL, NULL, 0, NULL, 0, "mkfs.jfs -V")!=0)
    {   errprintf("mkfs.jfs not found. please install jfsutils on your system or check the PATH.\n");
        return -1;
    }


    memset(options, 0, sizeof(options));

    strlcatf(options, sizeof(options), " %s ", fsoptions);

    if (dico_get_string(d, 0, FSYSHEADKEY_FSLABEL, buffer, sizeof(buffer))==0 && strlen(buffer)>0)
        strlcatf(options, sizeof(options), " -L '%s' ", buffer);

    if (exec_command(command, sizeof(command), &exitst, NULL, 0, NULL, 0, "mkfs.jfs -q %s %s", options, partition)!=0 || exitst!=0)
    {   errprintf("command [%s] failed\n", command);
        return -1;
    }


    memset(options, 0, sizeof(options));
    if (dico_get_string(d, 0, FSYSHEADKEY_FSUUID, buffer, sizeof(buffer))==0 && strlen(buffer)==36)
        strlcatf(options, sizeof(options), " -U %s ", buffer);

    if (options[0])
    {
        if (exec_command(command, sizeof(command), &exitst, NULL, 0, NULL, 0, "jfs_tune %s %s", partition, options)!=0 || exitst!=0)
        {   errprintf("command [%s] failed\n", command);
            return -1;
        }
    }

    return 0;
}

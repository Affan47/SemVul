read_info (int fd,
               bootInfo_t *bInfo)
{
    long i, j;
    char s[256];
    FILE *fp;

    bInfo->crc_on = check_crc(fd);
    if (bInfo->crc_on < 0)
        return (0);

    sendcommand(fd, REVISION);

    i = readval(fd);
    if(i < 0)
    {
        printf("Bootloader Version unknown (Fail)\n");
        bInfo->revision = -1;
    }
    else
    {
        printf("Bootloader    : V%lX.%lX\n", i>>8, i&0xFF);
        bInfo->revision = i;
    }

    sendcommand(fd, SIGNATURE);

    i = readval(fd);
    if (i < 0)
    {
        printf("Reading device SIGNATURE failed!\n\n");
        return (0);
    }
    bInfo->signature = i;

    if((fp = fopen("devices.txt", "r")) != NULL)
    {
        while(fgets(s, 256, fp))
        {
            if(sscanf(s, "%lX : %s", &j, s) == 2)
            {
                if(i == j)
                {
                    break;
                }
            }
            *s = 0;
        }
        fclose(fp);
    }
    else
    {

        for (j = 0; j < (sizeof (avr_dev) / sizeof (avrdev_t)); j++)
        {
            if (i == avr_dev[j].id)
            {
                strcpy (s, avr_dev[j].name);
                break;
            }
        }
        if (j == (sizeof (avr_dev) / sizeof (avrdev_t)))
        {
            sscanf ("(?)" , "%s", s);
            printf("File \"devices.txt\" not found!\n");
        }
    }
    printf("Target        : %06lX %s\n", i, s);

    sendcommand(fd, BUFFSIZE);

    i = readval(fd);
    if (i < 0)
    {
        printf("Reading BUFFSIZE failed!\n\n");
        return (0);
    }
    bInfo->buffsize = i;

    printf("Buffer        : %ld Byte\n", i );

    sendcommand(fd, USERFLASH);

    i = readval(fd);
    if (i < 0)
    {
        printf("Reading FLASHSIZE failed!\n\n");
        return (0);
    }
    if( i > MAXFLASH)
    {
        printf("Device and flashsize do not match!\n");
        return (0);
    }
    bInfo->flashsize = i;

    printf("Size available: %ld Byte\n", i );

    if(bInfo->crc_on != 2)
    {
        bInfo->crc_on = check_crc(fd);
        switch(bInfo->crc_on)
        {
            case 2:
                printf("No CRC support.\n");
                break;
            case 0:
                printf("CRC enabled and OK.\n");
                break;
            case 3:
                printf("CRC check failed!\n");
                break;
            default:
                printf("Checking CRC Error (%i)!\n", bInfo->crc_on);
                break;
        }
    }
    else
    {
        printf("No CRC support.\n\n");
    }

    return 1;
}

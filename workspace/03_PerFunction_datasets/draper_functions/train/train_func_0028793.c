new_summary_entry(struct image_summary *prev_entry,int fileformat,int datatype)
{
    struct image_summary *new = NULL;
    int chpr = 0;


    switch(datatype)
    {
        case EXIF_IFD:
        case INTEROP_IFD:
        case GPS_IFD:
            break;
        default:
            if(Debug & SCAN_DEBUG)
            {
                chpr = newline(1);
                printred("DEBUG: NEW SUMMARY ");
            }
            new = (struct image_summary *)malloc(sizeof(struct image_summary));
            if(new)
            {
                if(Debug & SCAN_DEBUG)
                    printf("%#lx\n",(unsigned long)new);
                memset(new,0,sizeof(struct image_summary));
                new->datatype = datatype;
                new->ifdnum = -1;
                new->subifdnum = -1;
                new->length = 0;
                new->offset = 0;
                new->subfiletype = -1;
                memset(new->filesubformatAPPN,0,16);
                if(prev_entry)
                {
                    if(Debug & SCAN_DEBUG)
                    {
                        printred("DEBUG: PREV ENTRY ");
                        chpr += printf("%#x, next=%#x, offset=%ld, lock=%d",
                                        (unsigned int)prev_entry,
                                        (unsigned int)prev_entry->next_entry,
                                        prev_entry->offset,prev_entry->entry_lock);
                        chpr = newline(chpr);
                    }

                    while(prev_entry->next_entry)
                    {
                        prev_entry = prev_entry->next_entry;
                        if(Debug & SCAN_DEBUG)
                        {
                            printred(" PREV ENTRY ");
                            chpr += printf("%#x, next=%#x, offset=%ld, lock=%d",
                                            (unsigned int)prev_entry,
                                            (unsigned int)prev_entry->next_entry,
                                            prev_entry->offset,prev_entry->entry_lock);
                            chpr = newline(chpr);
                        }
                    }
                    new->prev_entry = prev_entry;
                    if(Debug & SCAN_DEBUG)
                    {
                        printred("DEBUG: FOUND PREV ENTRY ");
                        chpr += printf("%#x, next=%#x, offset=%ld, lock=%d",
                                            (unsigned int)prev_entry,
                                            (unsigned int)prev_entry->next_entry,
                                            prev_entry->offset,prev_entry->entry_lock);
                        chpr = newline(chpr);
                    }
                    if(prev_entry->fileformat)
                        new->fileformat = prev_entry->fileformat;
                    prev_entry->next_entry = new;
                    if(Debug & SCAN_DEBUG)
                    {
                        printred("DEBUG: NEW ENTRY ");
                        chpr += printf(" next=%#x, prev offset=%d, prev lock=%d",
                                            (unsigned int)prev_entry->next_entry,
                                            (unsigned int)prev_entry->offset,prev_entry->entry_lock);
                        chpr = newline(chpr);
                    }
                }
                else
                    new->fileformat = fileformat;
            }
            else
            {
                printred("Memory allocation for image summary failed");
                if(prev_entry)
                    chpr += printf(" summary will be incomplete");
                else
                    chpr += printf(" no summary will be printed");
                newline(chpr);
            }
            if(Debug & SCAN_DEBUG)
                chpr = newline(1);
            break;
    }
    return(new);
}

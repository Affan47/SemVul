translate_temp_filename(int i)
{   char *p;
    switch(i)
    {   case 1: p=Temp1_Name; break;
        case 2: p=Temp2_Name; break;
        case 3: p=Temp3_Name; break;
    }
    if (strlen(Temporary_Path)+strlen(Temporary_File)+6 >= PATHLEN) {
        printf ("Temporary_Path is too long.\n");
        exit(1);
    }
    sprintf(p,"%s%s%d", Temporary_Path, Temporary_File, i);
#ifdef INCLUDE_TASK_ID
    sprintf(p+strlen(p), "_proc%08lx", (long int) unique_task_id());
#endif
#ifdef FILE_EXTENSIONS
    sprintf(p+strlen(p), ".tmp");
#endif
}

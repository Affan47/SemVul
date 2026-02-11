load_sourcefile(char *filename_given, int same_directory_flag)
{


    char name[PATHLEN]; int x = 0; FILE *handle;

    if (input_file == MAX_SOURCE_FILES)
        memoryerror("MAX_SOURCE_FILES", MAX_SOURCE_FILES);

    do
    {   x = translate_in_filename(x, name, filename_given, same_directory_flag,
                (input_file==0)?1:0);
        handle = fopen(name,"r");
    } while ((handle == NULL) && (x != 0));

    if (filename_storage_left <= (int)strlen(name))
        memoryerror("MAX_SOURCE_FILES", MAX_SOURCE_FILES);

    filename_storage_left -= strlen(name)+1;
    strcpy(filename_storage_p, name);
    InputFiles[input_file].filename = filename_storage_p;

    filename_storage_p += strlen(name)+1;

    if (debugfile_switch)
    {   write_debug_byte(FILE_DBR); write_debug_byte(input_file + 1);
        write_debug_string(filename_given);
        write_debug_string(name);
    }

    InputFiles[input_file].handle = handle;
    if (InputFiles[input_file].handle==NULL)
        fatalerror_named("Couldn't open source file", name);

    if (line_trace_level > 0) printf("\nOpening file \"%s\"\n",name);

    input_file++;
}

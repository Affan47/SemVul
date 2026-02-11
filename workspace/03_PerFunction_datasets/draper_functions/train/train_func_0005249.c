Test_C64(T_IO_Context * context)
{
    FILE* file;
    char filename[MAX_PATH_CHARACTERS];
    long file_size;

    Get_full_filename(filename, context->File_name, context->File_directory);

    file = fopen(filename,"rb");

    if (file)
    {
        file_size = File_length_file(file);
        switch (file_size)
        {
            case 1000:
            case 1002:
            case 8000:
            case 8002:
            case 9000:
            case 9002:
            case 10001:
            case 10003:
                File_error = 0;
                break;
            default:
            File_error = 1;
        }
        fclose (file);
    }
    else
    {
        File_error = 1;
    }
}

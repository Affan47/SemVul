Save_C64(T_IO_Context * context)
{
    char filename[MAX_PATH_CHARACTERS];
    static byte saveWhat=0, loadAddr=0;
    dword numcolors,cusage[256];
    numcolors=Count_used_colors(cusage);

    Get_full_filename(filename, context->File_name, context->File_directory);

    if (numcolors>16)
    {
        Warning_message("Error: Max 16 colors");
        File_error = 1;
        return;
    }
    if (((context->Width!=320) && (context->Width!=160)) || context->Height!=200)
    {
        Warning_message("must be 320x200 or 160x200");
        File_error = 1;
        return;
    }

    if(!Save_C64_window(&saveWhat,&loadAddr))
    {
        File_error = 1;
        return;
    }


    if (context->Width==320)
        File_error = Save_C64_hires(context,filename,saveWhat,loadAddr);
    else
        File_error = Save_C64_multi(context,filename,saveWhat,loadAddr);
}

environment(char *structure, char *format,char *ofile)
{
    struct input_file *f=files;
    char *file_names;
    size_t files_len = 1024,used = 0;

    set_env("FFE_STRUCTURE",structure);
    set_env("FFE_OUTPUT",ofile);
    set_env("FFE_FORMAT",format);
    set_env("FFE_FIRST_FILE",f->name);
    file_names = xmalloc(files_len);
    file_names[0] = 0;
    while(f != NULL)
    {
        used += strlen(f->name) + 1;
        if(used > files_len)
        {
            files_len *= 2;
            file_names = xrealloc(file_names,files_len);
        }
        strcat(file_names,f->name);
        if(f->next != NULL) strcat(file_names," ");
        f = f->next;
    }
    set_env("FFE_FILES",file_names);
    free(file_names);
}

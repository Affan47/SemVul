read_file(const char *filepath, char **buffer)
{
    FILE *fp;
    size_t file_size;


    if((fp = fopen(filepath, "rb")) == NULL)
    {
        printf("Cannot open file\n");
        return 0;
    }

    fseek(fp, 0L, SEEK_END);
    file_size = ftell(fp);
    rewind(fp);

    if((*buffer = (char*)calloc(1, sizeof(char) * (file_size))) == NULL)
    {
        printf("Memory allocation failed\n");
        fclose(fp);
        return 0;
    }

    if(fread(*buffer, file_size, 1, fp) != 1)
    {
        printf("Unable to read from the file\n");
        free(*buffer);
        fclose(fp);
	    return 0;
    }

    fclose(fp);

    return file_size;
}

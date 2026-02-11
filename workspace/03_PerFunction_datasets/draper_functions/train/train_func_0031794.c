ajFileSetEof(AjPFile file)
{
    AjBool ret = file->End;
    char c;

    fseek(file->fp, 0, SEEK_END);
    fread(&c, 1, 1, file->fp);

    if(feof(file->fp))
        file->End = ajTrue;
    else
        file->End = ajFalse;

    return ret;
}

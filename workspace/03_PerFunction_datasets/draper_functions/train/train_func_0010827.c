AsCheckForDirectory (
    char                    *SourceDirPath,
    char                    *TargetDirPath,
    char                    *Filename,
    char                    **SourcePath,
    char                    **TargetPath)
{
    char                    *SrcPath;
    char                    *TgtPath;


    if (!(strcmp (Filename, ".")) ||
        !(strcmp (Filename, "..")))
    {
        return (-1);
    }

    SrcPath = calloc (strlen (SourceDirPath) + strlen (Filename) + 2, 1);
    if (!SrcPath)
    {
        printf ("Could not allocate buffer for directory source pathname\n");
        return (-1);
    }

    TgtPath = calloc (strlen (TargetDirPath) + strlen (Filename) + 2, 1);
    if (!TgtPath)
    {
        printf ("Could not allocate buffer for directory target pathname\n");
        free (SrcPath);
        return (-1);
    }

    strcpy (SrcPath, SourceDirPath);
    strcat (SrcPath, "/");
    strcat (SrcPath, Filename);

    strcpy (TgtPath, TargetDirPath);
    strcat (TgtPath, "/");
    strcat (TgtPath, Filename);

    *SourcePath = SrcPath;
    *TargetPath = TgtPath;
    return (0);
}

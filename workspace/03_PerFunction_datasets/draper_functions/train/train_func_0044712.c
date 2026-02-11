ucftp_create_path(struct ucftpentry *ent)
{
    char *path;

    if(ent->parent == NULL)
        return av_strdup("");

    path = ucftp_create_path(ent->parent);

    return av_stradd(path, "/", ent->name, NULL);
}

ucftp_free_dirlist(struct ucftpentry *ent)
{
    if(ent->node != NULL) {
        struct ucftpentry *subent = ent->node->subdir;

        while(subent != NULL) {
            ucftp_free_tree(subent);

            subent = ent->node->subdir;
        }
    }
}

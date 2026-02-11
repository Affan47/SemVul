archive_write_mtree_destroy(struct archive_write *a)
{
    struct mtree_writer *mtree= a->format_data;

    if (mtree == NULL)
        return (ARCHIVE_OK);

    archive_entry_free(mtree->entry);
    archive_string_free(&mtree->ebuf);
    archive_string_free(&mtree->buf);
    archive_string_free(&mtree->set.parent);
    free(mtree);
    a->format_data = NULL;
    return (ARCHIVE_OK);
}

dc1394_camera_free_list (dc1394camera_list_t *list)
{
    if (list)
        free (list->ids);
    list->ids = NULL;
    free (list);
}

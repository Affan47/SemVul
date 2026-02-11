qof_instance_increase_editlevel (gpointer ptr)
{
    g_return_if_fail(QOF_IS_INSTANCE(ptr));
    GET_PRIVATE(ptr)->editlevel++;
}

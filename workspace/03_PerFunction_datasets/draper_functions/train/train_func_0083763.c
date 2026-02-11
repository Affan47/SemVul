qof_query_init (void)
{
    ENTER (" ");
    qof_query_core_init ();
    qof_class_init ();
    LEAVE ("Completed initialization of QofQuery");
}

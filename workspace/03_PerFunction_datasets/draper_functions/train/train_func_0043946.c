_child_data_new (void)
{
        ChildData *cd;

        cd = g_new0 (ChildData, 1);
        cd->refcount = 1;
        g_debug ("Allocated ChildData %p", cd);

        return cd;
}

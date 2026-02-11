push_anon_system (equation_system *sys)
{
    equation_system *old = get_anon_system_at_depth(sys->fd);

    if (old != NULL) {
	sysstack = g_list_remove(sysstack, old);
	gretl_object_unref(old, GRETL_OBJ_SYS);
    }

    gretl_object_ref(sys, GRETL_OBJ_SYS);
    sysstack = g_list_append(sysstack, sys);
}

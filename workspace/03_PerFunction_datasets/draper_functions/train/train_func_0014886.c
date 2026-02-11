delete_anonymous_equation_system (int level)
{
    equation_system *sys = get_anon_system_at_depth(level);

    if (sys != NULL) {
	sysstack = g_list_remove(sysstack, sys);
	gretl_object_unref(sys, GRETL_OBJ_SYS);
    }
}

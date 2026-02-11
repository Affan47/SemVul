menu_position_func_caller(GtkMenu *m, gint *x, gint *y, gboolean *push_in, gpointer data)
 {
    ScmObj func = SCM_OBJ(data), r;
    SCM_ASSERT(SCM_PROCEDUREP(func));
    r = Scm_GtkApply(func, SCM_LIST1(Scm_MakeGObject(G_OBJECT(m))));
    *x = 0; *y = 0; *push_in = FALSE;
    if (Scm_Length(r) != 3) {
       Scm_Warn("gtk-menu-popup manu position callback %S returned bad number of values (%d), which is supposed to be 3.  The result is ignored.", func, Scm_Length(r));
       return;
    }
    if (!SCM_INTP(SCM_CAR(r))) {
       Scm_Warn("gtk-menu-popup manu position callback %S returned bad type of value %S as the first return value, which is supposed to be an integer.  The result is ignored.", func, SCM_CAR(r));
       return;
    }
    *x = SCM_INT_VALUE(SCM_CADR(r));
    if (!SCM_INTP(SCM_CADR(r))) {
       Scm_Warn("gtk-menu-popup manu position callback %S returned bad type of value %S as the second return value, which is supposed to be an integer.  The result is ignored.", func, SCM_CADR(r));
       return;
    }
    *y = SCM_INT_VALUE(SCM_CADR(r));
    *push_in = SCM_BOOL_VALUE(SCM_CAR(SCM_CDDR(r)));
 }

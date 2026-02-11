Scm_GdkDragContextClass_actions_SET(ScmObj OBJARG, ScmObj value)
{
  GdkDragContext* obj = SCM_GDK_DRAG_CONTEXT(OBJARG);
  if (!SCM_INTEGERP(value)) Scm_Error("int required, but got %S", value);
  obj->actions = Scm_GetInteger(value);
}

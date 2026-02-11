visu_ui_curve_frame_new(float distMin, float distMax)
{
  GtkWidget *obj;

  g_return_val_if_fail(distMin >= 0.f && distMax > distMin, (GtkWidget*)0);

  obj = g_object_new(VISU_UI_TYPE_CURVE_FRAME, NULL);
  g_return_val_if_fail(obj, (GtkWidget*)0);

  visu_ui_curve_frame_init(VISU_UI_CURVE_FRAME(obj));
  VISU_UI_CURVE_FRAME(obj)->dists[0] = distMin;
  VISU_UI_CURVE_FRAME(obj)->dists[1] = distMax;

  return obj;
}

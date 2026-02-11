gui_relation_submit(GtkWidget        *widget,
                      gint              type,
                      gpointer          value,
                      gboolean          direct,
                      struct model_pak *model)
{
struct relation_pak *relation;


relation = g_malloc(sizeof(struct relation_pak));
relation->direct = direct;
relation->type = type;
if (model)
  relation->offset = value - (gpointer) model;
else
  relation->offset = 0;
relation->variable = value;
relation->model = model;
relation->widget = widget;


if (!direct)
  g_assert(relation->offset > 0);

#if DEBUG_RELATION
printf("submit: ");
printf("[%p type %d]", relation, type);
if (model)
  {
  if (direct)
    printf("[model %d][value %p]", model->number, value);
  else
    printf("[model %d][value %p][offset %d]", model->number, value, relation->offset);
  }
printf("\n");
#endif

switch (relation->type)
  {
  case AUTO_CHECK:
    if (*((gint *) value))
      gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(widget), TRUE);
    else
      gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(widget), FALSE);
    break;

  case AUTO_SPIN:
    gtk_spin_button_set_value(GTK_SPIN_BUTTON(widget), *((gdouble *) value));
    break;

  case AUTO_RANGE:
    gtk_range_set_value(GTK_RANGE(widget), *((gint *) value));
    break;
  }

gui_relation_list = g_slist_prepend(gui_relation_list, relation);
}

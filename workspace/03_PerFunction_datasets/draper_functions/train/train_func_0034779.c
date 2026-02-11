for_each_symbol (gchar * name, AsmSymEntry * entry, gpointer dialog)
{
  GtkWidget *dig;
  GList **lst = NULL;

  g_assert (entry);
  g_assert (dialog);

  dig = GTK_WIDGET (dialog);


  switch (entry->type)
	{
	case ASM_SYM_VARIABLE:
	  lst = &list_variables;
	  break;
	case ASM_SYM_LABEL:
	  lst = &list_labels;
	  break;
	case ASM_SYM_MACRO:
	  lst = &list_macros;
	  break;
	default:
	  return;
	}

  *lst = g_list_insert (*lst, (gpointer) entry->name, -1);
}

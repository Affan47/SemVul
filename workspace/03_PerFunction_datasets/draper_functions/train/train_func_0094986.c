get_status_icon (GtkTreeView *tree_view, CutTestResultStatus status)
{
    GdkPixbuf *icon;
    const gchar *stock_id = "";

    switch (status) {
      case CUT_TEST_RESULT_SUCCESS:
        stock_id = GTK_STOCK_APPLY;
        break;
      case CUT_TEST_RESULT_NOTIFICATION:
        stock_id = GTK_STOCK_DIALOG_WARNING;
        break;
      case CUT_TEST_RESULT_OMISSION:
        stock_id = GTK_STOCK_DIALOG_ERROR;
        break;
      case CUT_TEST_RESULT_PENDING:
        stock_id = GTK_STOCK_DIALOG_ERROR;
        break;
      case CUT_TEST_RESULT_FAILURE:
        stock_id = GTK_STOCK_STOP;
        break;
      case CUT_TEST_RESULT_ERROR:
        stock_id = GTK_STOCK_CANCEL;
        break;
      case CUT_TEST_RESULT_CRASH:
        stock_id = GTK_STOCK_STOP;
        break;
      default:
        stock_id = GTK_STOCK_INFO;
        break;
    }
    icon = gtk_widget_render_icon(GTK_WIDGET(tree_view),
                                  stock_id, GTK_ICON_SIZE_MENU,
                                  NULL);

    return icon;
}

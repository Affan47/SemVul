ComposeWindow_init(clawsmail_ComposeWindowObject *self, PyObject *args, PyObject *kwds)
{
  MainWindow *mainwin;
  PrefsAccount *ac = NULL;
  FolderItem *item;
  GList* list;
  GList* cur;
  gboolean did_find_compose;
  Compose *compose = NULL;
  const char *ss;
  unsigned char open_window;


  static char *kwlist[] = {"address", "__open_window", NULL};

  ss = NULL;
  open_window = 1;
  PyArg_ParseTupleAndKeywords(args, kwds, "|sb", kwlist, &ss, &open_window);

  if(open_window) {
    mainwin = mainwindow_get_mainwindow();
    item = mainwin->summaryview->folder_item;
    did_find_compose = FALSE;

    if(ss) {
      ac = account_find_from_address(ss, FALSE);
      if (ac && ac->protocol != A_NNTP) {
        compose = compose_new_with_folderitem(ac, item, NULL);
        did_find_compose = TRUE;
      }
    }
    if(!did_find_compose) {
      if (item) {
        ac = account_find_from_item(item);
        if (ac && ac->protocol != A_NNTP) {
          compose = compose_new_with_folderitem(ac, item, NULL);
          did_find_compose = TRUE;
        }
      }


      if (!did_find_compose && cur_account && (cur_account->protocol != A_NNTP)) {
        compose = compose_new_with_folderitem(cur_account, item, NULL);
        did_find_compose = TRUE;
      }

      if(!did_find_compose) {

        list = account_get_list();
        for (cur = list ; cur != NULL ; cur = g_list_next(cur)) {
          ac = (PrefsAccount *) cur->data;
          if (ac->protocol != A_NNTP) {
            compose = compose_new_with_folderitem(ac, item, NULL);
            did_find_compose = TRUE;
          }
        }
      }
    }

    if(!did_find_compose)
      return -1;

    composewindow_set_compose(self, compose);
    gtk_widget_show_all(compose->window);
    flush_gtk_queue();
  }
  return 0;
}

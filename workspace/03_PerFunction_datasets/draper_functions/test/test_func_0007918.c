search_todo(const char *needle, GtkWidget *clist)
{
   gchar *empty_line[] = { "","" };
   char str2[SEARCH_MAX_COLUMN_LEN+2];
   ToDoList *todo_list;
   ToDoList *temp_todo;
   struct search_record *new_sr;
   int found, count;
   int case_sense;


   todo_list = NULL;

   get_todos2(&todo_list, SORT_DESCENDING, 2, 2, 2, 1, CATEGORY_ALL);

   if (todo_list==NULL) {
      return 0;
   }

   count = 0;
   case_sense = GTK_TOGGLE_BUTTON(case_sense_checkbox)->active;

   for (temp_todo = todo_list; temp_todo; temp_todo=temp_todo->next) {
      found = 0;
      if ( (temp_todo->mtodo.todo.description) &&
           (temp_todo->mtodo.todo.description[0]) ) {
         if ( jp_strstr(temp_todo->mtodo.todo.description, needle, case_sense) ) {
            found = 1;
         }
      }
      if ( !found &&
           (temp_todo->mtodo.todo.note) &&
           (temp_todo->mtodo.todo.note[0]) ) {
         if ( jp_strstr(temp_todo->mtodo.todo.note, needle, case_sense) ) {
            found = 2;
         }
      }

      if (found) {
         gtk_clist_prepend(GTK_CLIST(clist), empty_line);
         gtk_clist_set_text(GTK_CLIST(clist), 0, 0, _("todo"));
         if (found == 1) {
            lstrncpy_remove_cr_lfs(str2, temp_todo->mtodo.todo.description, SEARCH_MAX_COLUMN_LEN);
         } else {
            lstrncpy_remove_cr_lfs(str2, temp_todo->mtodo.todo.note, SEARCH_MAX_COLUMN_LEN);
         }
         gtk_clist_set_text(GTK_CLIST(clist), 0, 1, str2);


         new_sr = malloc(sizeof(struct search_record));
         new_sr->app_type = TODO;
         new_sr->plugin_flag = 0;
         new_sr->unique_id = temp_todo->mtodo.unique_id;
         new_sr->next = search_rl;
         search_rl = new_sr;

         gtk_clist_set_row_data(GTK_CLIST(clist), 0, new_sr);

         count++;
      }
   }

   jp_logf(JP_LOG_DEBUG, "calling free_ToDoList\n");
   free_ToDoList(&todo_list);

   return count;
}

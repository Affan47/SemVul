task_free(gpointer data)
{
struct task_pak *task = data;

g_assert(task != NULL);

g_free(task->label);
g_free(task->time);
g_free(task->message);
g_free(task->status_file);

if (task->status_fp)
  fclose(task->status_fp);

g_string_free(task->status_text, TRUE);

g_free(task);
}

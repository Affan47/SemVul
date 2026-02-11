compile_methods(bool do_main)
{
int method_count = java_class->get_method_count();
char method_name[32];
int index;
bool did_execute_statics = false;

  for (index = 0; index < method_count; index++)
  {
    if (java_class->get_method_name(method_name, sizeof(method_name), index) == 0)
    {
      if (strcmp(method_name, "main") == 0)
      {
        if (!do_main) { continue ;}
        if (compile_method(java_class, index) != 0)
        {
          printf("** Error compiling class.\n");
          return -1;
        }

        break;
      }

      if (do_main) { continue; }

      if (strcmp("<clinit>", method_name) == 0)
      {
        if (execute_statics(index) != 0) { return -1; }
        did_execute_statics = true;
        continue;
      }

      if (compile_method(java_class, index) != 0)
      {
        printf("** Error compiling class.\n");
        return -1;
      }
    }
  }

  if (!did_execute_statics && !do_main && external_classes.size() != 0)
  {
    execute_statics(-1);
  }

  return 0;
}

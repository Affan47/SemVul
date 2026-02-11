ecore_exe_tag_set(Ecore_Exe  *exe,
                  const char *tag)
{
   EINA_MAIN_LOOP_CHECK_RETURN;
   if (!ECORE_MAGIC_CHECK(exe, ECORE_MAGIC_EXE))
   {
      ECORE_MAGIC_FAIL(exe, ECORE_MAGIC_EXE, "ecore_exe_tag_set");
      return;
   }
   IF_FREE(exe->tag);
   if (tag)
     exe->tag = strdup(tag);
   else
     exe->tag = NULL;
}

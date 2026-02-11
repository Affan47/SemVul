MakefileColorEcho(int color, const char* message,
                                      bool newline, bool enabled)
{


  int assumeTTY = cmsysTerminal_Color_AssumeTTY;
  if(cmSystemTools::GetEnv("DART_TEST_FROM_DART") ||
     cmSystemTools::GetEnv("DASHBOARD_TEST_FROM_CTEST") ||
     cmSystemTools::GetEnv("CTEST_INTERACTIVE_DEBUG_MODE"))
    {

    assumeTTY = 0;
    }

  if(enabled)
    {
    cmsysTerminal_cfprintf(color | assumeTTY, stdout, "%s%s",
                           message, newline? "\n" : "");
    }
  else
    {

    fprintf(stdout, "%s%s", message, newline? "\n" : "");
    }
}

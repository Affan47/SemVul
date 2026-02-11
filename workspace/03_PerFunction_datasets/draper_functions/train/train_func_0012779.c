_cogl_parse_debug_string (const char *value,
                          CoglBool enable,
                          CoglBool ignore_help)
{
  if (ignore_help && strcmp (value, "help") == 0)
    return;


  if (strcmp (value, "all") == 0 ||
      strcmp (value, "verbose") == 0)
    {
      int i;
      for (i = 0; i < n_cogl_log_debug_keys; i++)
        if (enable)
          COGL_DEBUG_SET_FLAG (cogl_log_debug_keys[i].value);
        else
          COGL_DEBUG_CLEAR_FLAG (cogl_log_debug_keys[i].value);
    }
  else if (g_ascii_strcasecmp (value, "help") == 0)
    {
      g_printerr ("\n\n%28s\n", _("Supported debug values:"));
#define OPT(MASK_NAME, GROUP, NAME, NAME_FORMATTED, DESCRIPTION) \
      g_printerr ("%28s %s\n", NAME ":", g_dgettext (GETTEXT_PACKAGE, \
                                                     DESCRIPTION));
#include "cogl-debug-options.h"
      g_printerr ("\n%28s\n", _("Special debug values:"));
      OPT (IGNORED, "ignored", "all", "ignored", \
           N_("Enables all non-behavioural debug options"));
      OPT (IGNORED, "ignored", "verbose", "ignored", \
           N_("Enables all non-behavioural debug options"));
#undef OPT

      g_printerr ("\n"
                  "%28s\n"
                  " COGL_DISABLE_GL_EXTENSIONS: %s\n"
                  "   COGL_OVERRIDE_GL_VERSION: %s\n",
                  _("Additional environment variables:"),
                  _("Comma-separated list of GL extensions to pretend are "
                    "disabled"),
                  _("Override the GL version that Cogl will assume the driver "
                    "supports"));
      exit (1);
    }
  else
    {
      _cogl_parse_debug_string_for_keys (value,
                                         enable,
                                         cogl_log_debug_keys,
                                         n_cogl_log_debug_keys);
      _cogl_parse_debug_string_for_keys (value,
                                         enable,
                                         cogl_behavioural_debug_keys,
                                         n_cogl_behavioural_debug_keys);
    }
}

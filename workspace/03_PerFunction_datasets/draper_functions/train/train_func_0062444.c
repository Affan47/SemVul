usage(user_interaction & dialog, const char *command_name)
{
    string name;
    tools_extract_basename(command_name, name);
    shell_interaction_change_non_interactive_output(&cout);

    dialog.printf(gettext("usage: %s [ -c | -x | -d | -t | -l | -C | -+ ] [<path>/]<basename> [options...]\n"), name.c_str());
    dialog.printf("       %s -h\n", name.c_str());
    dialog.printf("       %s -V\n", name.c_str());
#include "dar.usage"
}

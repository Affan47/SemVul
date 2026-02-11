luB(enum usage_level ul, const char *command)
{
    int is_my_command = (command && 0 == strcmp(command, "B"));
    if (ul == usage_all || !command || is_my_command)
    FPS "%-15s Run a series of certutil commands from a batch file\n", "-B");
    if (ul == usage_selected && !is_my_command)
        return;
    FPS "%-20s Specify the batch file\n", "   -i batch-file");
}

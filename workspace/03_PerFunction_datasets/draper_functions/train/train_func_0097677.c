pop_commands(std::vector<CdlInterpreterCommandEntry>* original_commands)
{
    CYG_REPORT_FUNCNAME("CdlInterpreter::pop_commands");
    CYG_REPORT_FUNCARG2XV(this, &original_commands);
    CYG_PRECONDITION_THISC();
    CYG_PRECONDITION(0 != current_commands, "no pop without a previous push please");

    std::vector<CdlInterpreterCommandEntry>::iterator i;

    for (i = current_commands->begin(); i != current_commands->end(); i++) {
        remove_command(i->name);
    }


    if (0 != original_commands) {
        for (i = original_commands->begin(); i != original_commands->end(); i++) {
            add_command(i->name, i->command);
        }
    }
    current_commands = original_commands;
    CYG_REPORT_RETURN();
}

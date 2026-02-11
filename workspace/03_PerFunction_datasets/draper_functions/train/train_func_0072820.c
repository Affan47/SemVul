log_set_output_level(enum output_level level)
{
    int i;

    for (i = 0; i < num_logfiles; ++i) {
        if (logfiles[i].file == stderr) {
            logfiles[i].minimum_output_level = level;
            break;
        }
    }
}

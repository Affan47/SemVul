opal_output_set_verbosity(int output_id, int level)
{
    if (output_id >= 0 && output_id < OPAL_OUTPUT_MAX_STREAMS) {
        info[output_id].ldi_verbose_level = level;
    }
}

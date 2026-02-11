gva_process_stderr_read_lines (GvaProcess *process)
{
        guint num_lines, ii;
        gchar **lines = NULL;

        g_return_val_if_fail (GVA_IS_PROCESS (process), NULL);

        num_lines = gva_process_stderr_num_lines (process);

        if (num_lines > 0)
        {
                lines = g_new0 (gchar *, num_lines + 1);

                for (ii = 0; ii < num_lines; ii++)
                {
                        lines[ii] = gva_process_stderr_read_line (process);
                        g_assert (lines[ii] != NULL);
                }
        }

        return lines;
}

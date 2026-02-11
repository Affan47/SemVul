explain_buffer_ide_task_request_t(explain_string_buffer_t *sb,
    const ide_task_request_t *data)
{
    if (explain_is_efault_pointer(data, sizeof(*data)))
    {
        explain_buffer_pointer(sb, data);
        return;
    }

    explain_string_buffer_puts(sb, "{ io_ports = ");
    explain_buffer_char_data(sb, data->io_ports, sizeof(data->io_ports));
    explain_string_buffer_puts(sb, ", hob_ports = ");
    explain_buffer_char_data(sb, data->hob_ports, sizeof(data->hob_ports));
    explain_string_buffer_puts(sb, ", out_flags = ");
    explain_buffer_ide_reg_valid_t(sb, data->out_flags);
    explain_string_buffer_puts(sb, ", in_flags = ");
    explain_buffer_ide_reg_valid_t(sb, data->in_flags);
    explain_string_buffer_puts(sb, ", data_phase = ");
    explain_buffer_int(sb, data->data_phase);
    explain_string_buffer_puts(sb, ", req_cmd = ");
    explain_buffer_req_cmd(sb, data->req_cmd);
    explain_string_buffer_puts(sb, ", out_size = ");
    explain_buffer_ulong(sb, data->out_size);
    explain_string_buffer_puts(sb, ", in_size = ");
    explain_buffer_ulong(sb, data->in_size);
    explain_string_buffer_puts(sb, " }");
}

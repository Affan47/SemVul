gnc_table_get_io_flags (Table *table, VirtualLocation virt_loc)
{
    TableGetCellIOFlagsHandler io_flags_handler;
    const char *cell_name;
    CellIOFlags flags;

    if (!table || !table->model)
        return XACC_CELL_ALLOW_NONE;

    cell_name = gnc_table_get_cell_name (table, virt_loc);

    io_flags_handler = gnc_table_model_get_io_flags_handler (table->model,
                       cell_name);
    if (!io_flags_handler)
        return XACC_CELL_ALLOW_NONE;

    flags = io_flags_handler (virt_loc, table->model->handler_user_data);

    if (gnc_table_model_read_only (table->model))
        flags &= XACC_CELL_ALLOW_SHADOW;

    return flags;
}

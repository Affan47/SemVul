gnc_date_cell_init (DateCell *cell)
{
    PopBox *box;
    time64 secs;
    char buff[DATE_BUF];

    gnc_basic_cell_init (&(cell->cell));

    cell->cell.is_popup = TRUE;

    cell->cell.destroy = gnc_date_cell_destroy;

    cell->cell.gui_realize = gnc_date_cell_realize;
    cell->cell.gui_destroy = gnc_date_cell_gui_destroy;
    cell->cell.modify_verify = gnc_date_cell_modify_verify;
    cell->cell.direct_update = gnc_date_cell_direct_update;
    cell->cell.set_value = gnc_date_cell_set_value_internal;

    box = g_new0 (PopBox, 1);

    box->sheet = NULL;
    box->item_edit = NULL;
    box->date_picker = NULL;

    box->signals_connected = FALSE;
    box->calendar_popped = FALSE;
    box->in_date_select = FALSE;

    cell->cell.gui_private = box;


    gnc_time (&secs);
    gnc_localtime_r (&secs, &(box->date));
    gnc_date_cell_print_date (cell, buff);

    gnc_basic_cell_set_value_internal (&cell->cell, buff);
}

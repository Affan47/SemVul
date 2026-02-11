check_and_set_cell_renderer (GtkTreeViewColumn *column,
                             GtkCellRenderer   *renderer,
                             gint               i)
{

    switch (i) {


    case SAT_LIST_COL_AZ:
    case SAT_LIST_COL_EL:
    case SAT_LIST_COL_RA:
    case SAT_LIST_COL_DEC:
    case SAT_LIST_COL_MA:
    case SAT_LIST_COL_PHASE:
        gtk_tree_view_column_set_cell_data_func (column,
                                                 renderer,
                                                 degree_cell_data_function,
                                                 GUINT_TO_POINTER (i),
                                                 NULL);
        break;


    case SAT_LIST_COL_LAT:
    case SAT_LIST_COL_LON:
        gtk_tree_view_column_set_cell_data_func (column,
                                                 renderer,
                                                 latlon_cell_data_function,
                                                 GUINT_TO_POINTER (i),
                                                 NULL);
        break;


    case SAT_LIST_COL_RANGE:
    case SAT_LIST_COL_ALT:
    case SAT_LIST_COL_FOOTPRINT:
        gtk_tree_view_column_set_cell_data_func (column,
                                                 renderer,
                                                 distance_cell_data_function,
                                                 GUINT_TO_POINTER (i),
                                                 NULL);
        break;

    case SAT_LIST_COL_VEL:
    case SAT_LIST_COL_RANGE_RATE:
        gtk_tree_view_column_set_cell_data_func (column,
                                                 renderer,
                                                 range_rate_cell_data_function,
                                                 GUINT_TO_POINTER (i),
                                                 NULL);
        break;

    case SAT_LIST_COL_DOPPLER:
        gtk_tree_view_column_set_cell_data_func (column,
                                                 renderer,
                                                 float_to_int_cell_data_function,
                                                 GUINT_TO_POINTER (i),
                                                 NULL);
        break;

    case SAT_LIST_COL_DELAY:
    case SAT_LIST_COL_LOSS:
        gtk_tree_view_column_set_cell_data_func (column,
                                                 renderer,
                                                 two_dec_cell_data_function,
                                                 GUINT_TO_POINTER (i),
                                                 NULL);
        break;

    case SAT_LIST_COL_AOS:
    case SAT_LIST_COL_LOS:
        gtk_tree_view_column_set_cell_data_func (column,
                                                 renderer,
                                                 event_cell_data_function,
                                                 GUINT_TO_POINTER (i),
                                                 NULL);
        break;

    default:
        break;

    }

}

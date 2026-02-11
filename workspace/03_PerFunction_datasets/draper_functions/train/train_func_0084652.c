setrows_cb(Fl_Widget*, void *data)
{
    Fl_Input *in = (Fl_Input*)data;
    int rows = atoi(in->value());
    if ( rows < 0 ) rows = 0;
    G_table->rows(rows);
}

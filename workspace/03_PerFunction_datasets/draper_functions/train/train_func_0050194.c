get_grid_size (GtkSatModule *module, guint *rows, guint *cols)
{
    guint i;
    guint xmax = 0;
    guint ymax = 0;


    for (i = 0; i < module->nviews; i++) {
        xmax = MAX(xmax,module->grid[5*i+2]);
        ymax = MAX(ymax,module->grid[5*i+4]);
    }

    *cols = xmax;
    *rows = ymax;
}

compare_coordinates_y (gconstpointer a, gconstpointer b, gpointer data)
{
    double *ea = (double *)a;
    double *eb = (double *)b;

    if (ea[1] < eb[1]) {
        return -1;
    }

    else if (ea[1] > eb[1]) {
        return 1;
    }

    return 0;
}

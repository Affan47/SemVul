print_file_time_units(FILE * fp, enum siesta_time_measurement_type units)
{
    gint allok = 0;
    switch (units)
    {
        case S_TIME:            fprintf(fp, " s\n"); break;
        case FS_TIME:           fprintf(fp, " fs\n"); break;
        case PS_TIME:           fprintf(fp, " ps\n"); break;
        case NS_TIME:           fprintf(fp, " ns\n"); break;
        default:

            fprintf(fp," \n");
            allok = 1;
            break;
    }
    return allok;
}

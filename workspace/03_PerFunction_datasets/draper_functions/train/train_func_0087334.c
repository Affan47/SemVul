print_file_pressure_units(FILE * fp, enum siesta_pressure_measurement_type units)
{
    gint allok = 0;
    switch (units)
    {
        case P_PRES:                fprintf(fp, " Pa\n"); break;
        case MPA_PRES:              fprintf(fp, " MPa\n"); break;
        case GPA_PRES:              fprintf(fp, " GPa\n"); break;
        case ATM_PRES:              fprintf(fp, " atm\n"); break;
        case BAR_PRES:              fprintf(fp, " bar\n"); break;
        case MBAR_PRES:             fprintf(fp, " Mbar\n"); break;
        case RYBOHR3_PRES:          fprintf(fp, " Ry/Bohr**3\n"); break;
        case EVANG3_PRES:           fprintf(fp, " eV/Ang**3\n"); break;
        default:

            fprintf(fp," \n");
            allok = 1;
            break;
    }
    return allok;
}

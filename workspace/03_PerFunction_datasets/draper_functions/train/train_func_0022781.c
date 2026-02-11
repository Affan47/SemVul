TabbingGetColumnAlignments(char *row, char *align, int *n, int *next_left)


{
    int i;

    *next_left = g_tabbing_left_position;
    *n = *next_left + 1;

    for (i = 0; i < *n; i++)
        align[i] = 'l';

    while (row && *row) {

        if (*row != '\\') {
            row++;
            continue;
        }

        row++;
        row = skip_verb(row);

        switch (*row) {

            case '=':
                align[*n] = 'l';
                (*n)++;
                break;

            case '>':
                align[*n] = 'l';
                (*n)++;
                break;

            case '<':
                break;

            case '\'':
                align[*n - 2] = 'r';
                align[*n - 1] = 'l';
                break;

            case '`':
                align[*n] = 'r';
                (*n)++;
                break;

            case '+':
                (*next_left)++;
                break;

            case '-':
                (*next_left)--;
                break;

            default:
                break;
        }
    }
    align[*n] = '\0';

}

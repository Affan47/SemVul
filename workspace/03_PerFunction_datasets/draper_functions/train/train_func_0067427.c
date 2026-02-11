load_table_int(int **bonuses, FILE *fp, char *bonus_name)
{
    char buf[MAX_BUF], *cp;
    int on_stat = 0, tmp_bonus;

    *bonuses = calloc(settings.max_stat+1, sizeof(int));

    while (fgets(buf, MAX_BUF-1, fp) != NULL) {
        if (buf[0] == '#')
            continue;


        if (buf[0] == '\n')
            continue;


        if (buf[0] == '{')
            continue;

        if (buf[0] == '}') {
            if ((on_stat-1) != settings.max_stat) {
                LOG(llevError,"Number of bonus does not match max stat (%d!=%d, bonus=%s)\n",
                    on_stat, settings.max_stat, bonus_name);
                return 1;
            }
            else return 0;
        }


        cp = buf;
        while (*cp != 0) {

            while (!isdigit(*cp) && *cp!='.' && *cp!='-' && *cp!='+' && *cp != 0)
                cp++;

            if (*cp == 0) break;

            tmp_bonus = atoi(cp);

            if (on_stat > settings.max_stat) {
                LOG(llevError,"Number of bonus entries exceed max stat (line=%s, bonus=%s)\n",
                    buf, bonus_name);
                return 1;
            }
            (*bonuses)[on_stat] = tmp_bonus;
            on_stat++;


            while ((isdigit(*cp) || *cp=='-' || *cp=='+') && *cp != 0)
                cp++;
        }
    }

    LOG(llevError,"Reached end of file without getting close brace?  bonus=%s\n", bonus_name);
    return 1;
}

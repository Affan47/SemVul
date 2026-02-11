sayInstance(int instance)
{
#ifdef SAY_INSTANCE_WITH_PLAYER_WORDS_IF_PARAMETER
    int p, i;


    if (params != NULL)
        for (p = 0; params[p].code != EOF; p++)
            if (params[p].code == instance) {

                if (params[p].firstWord == EOF)
                    break;
                else {
                    char *capitalized;

                    for (i = params[p].firstWord; i <= params[p].lastWord-1; i++)
                        output((char *)pointerTo(dict[wrds[i]].wrd));

                    if (header->capitalizeNouns) {
                        capitalized = strdup((char *)pointerTo(dict[wrds[params[p].lastWord]].wrd));
                        capitalized[0] = IsoToUpperCase(capitalized[0]);
                        output(capitalized);
                        free(capitalized);
                    } else
                        output((char *)pointerTo(dict[wrds[params[p].lastWord]].wrd));
                }
                return;
            }
#endif
    if (!mention(instance))
        interpret(instances[instance].name);
}

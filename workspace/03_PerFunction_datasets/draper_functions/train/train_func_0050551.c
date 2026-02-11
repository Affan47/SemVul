poptPrintUsage(poptContext con, FILE * fp,  UNUSED(int flags))
{
    poptDone done = memset(alloca(sizeof(*done)), 0, sizeof(*done));
    size_t cursor;

    done->nopts = 0;
    done->maxopts = 64;
    cursor = done->maxopts * sizeof(*done->opts);

    done->opts = memset(alloca(cursor), 0, cursor);

    done->opts[done->nopts++] = (const void *) con->options;


    cursor = showHelpIntro(con, fp);
    cursor += showShortOptions(con->options, fp, NULL);
    cursor = singleTableUsage(con, fp, cursor, con->options, NULL, done);
    cursor = itemUsage(fp, cursor, con->aliases, con->numAliases, NULL);
    cursor = itemUsage(fp, cursor, con->execs, con->numExecs, NULL);

    if (con->otherHelp) {
	cursor += strlen(con->otherHelp) + 1;
	if (cursor > 79) fprintf(fp, "\n       ");
	fprintf(fp, " %s", con->otherHelp);
    }

    fprintf(fp, "\n");
}

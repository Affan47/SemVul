progress_init(Progress *p, UrlResource *rsrc, long int len)
{
        char *filename 	= NULL;
        int win_width	= 0;
        int total_units	= 0;

        if( !p )
                return 0;

        p->rsrc = rsrc;

#ifndef PROGRESS_DEFAULT_OFF
        if( rsrc->options & OPT_PROGRESS ) {
                p->tty = 1;
        } else {
                if( (!isatty(2)) || (rsrc->outfile[0] == '-') ||
                    (rsrc->options & OPT_QUIET) ) {

                        p->tty = 0;
                        return 1;
                } else {
                        p->tty = 1;
                }
        }
#else
        if( rsrc->options & OPT_PROGRESS )
                p->tty = 1;
        else {
                p->tty = 0;
                return 1;
        }
#endif

        win_width = guess_winsize();

        if( win_width > 30 )
                total_units = win_width - (30 + 9 + 16);
        else {

                total_units = 20;
        }

        p->length = len;


        setbuf(stderr, (char *)&output_buf);

        fprintf(stderr, "%s (", rsrc->url->full_url);

        if( total_units && len ) {
                p->length = len;
                p->max_hashes = total_units;
                fprintf(stderr, "%dK", (int )(len / 1024));
        } else {
                fprintf(stderr, "unknown size");
        }

        fprintf(stderr, ")\n");

        p->current = 0;

        filename = strdup(rsrc->outfile);

        if( strlen(filename) > 24 )
                filename[24] = '\0';

        fprintf(stderr, "%-25s[", filename);

        if( p->length )
                repchar(stderr, ' ', p->max_hashes);
        else
                fputc('+', stderr);

        fprintf(stderr, "] %7dK", (int )p->current);
        fflush(stderr);
        return 1;
}

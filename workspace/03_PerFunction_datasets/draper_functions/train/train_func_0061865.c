dup_filter(const unsigned char *buf, int len)
{
    struct dup_entry {
        timems_t        timems;
        unsigned char   rf_command[16];
        int             rf_cmd_len;
    };
    static struct dup_entry dups[16];
    int i, firstunused=-1, add_index, inuse=0;
    struct dup_entry *p;
    timems_t timems;

#define DUP_MAX         (sizeof(dups)/sizeof(dups[0]))

    timems = get_timems();
    for (i = 0; i < DUP_MAX; i++) {
        p = &dups[i];
        if (p->rf_cmd_len) {
            if ((p->rf_cmd_len == len) && (memcmp(p->rf_command, buf, len) == 0)) {


                if (timems > p->timems) {

                    p->timems = get_timems() + DUP_TIME;

                    return 0;
                }
                else {


                    return 1;
                }
            }
            else {
                if (timems > p->timems) {

                    p->rf_cmd_len = 0;
                    if (firstunused == -1) firstunused = i;
                }
                else
                    inuse++;
            }
        }
        else {
            if (firstunused == -1) firstunused = i;
        }
    }

    if (len == -1) return (inuse != 0);


    add_index = firstunused;
    if (firstunused == -1) {

        int min=dups[0].timems;
        add_index = 0;
        for (i = 1; i < DUP_MAX; i++) {
            if (dups[i].timems < min) {
                min = dups[i].timems;
                add_index = i;
            }
        }
    }

    p = &dups[add_index];
    p->timems = get_timems() + DUP_TIME;
    memcpy(p->rf_command, buf, len);
    p->rf_cmd_len = len;
    return 0;
}

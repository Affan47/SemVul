merge_ifconf(struct interface_conf *dest,
             const struct interface_conf *src1,
             const struct interface_conf *src2)
{

#define MERGE(field)                            \
    do {                                        \
        if(src1->field)                         \
            dest->field = src1->field;          \
        else                                    \
            dest->field = src2->field;          \
    } while(0)

    MERGE(hello_interval);
    MERGE(update_interval);
    MERGE(cost);
    MERGE(wired);
    MERGE(split_horizon);
    MERGE(lq);
    MERGE(faraway);
    MERGE(channel);

#undef MERGE
}

procopt(const char *opts, String *args, int *offsetp,
    struct timeval *ptime, struct World **world, int *disp, int *subflag,
    int *delay)
{
    char opt;
    const char *ptr;
    ValueUnion uval;

    *world = NULL;
    ptime->tv_sec = PTIME_VAR;
    startopt(CS(args), opts);
    while ((opt = nextopt(&ptr, &uval, NULL, offsetp))) {
        switch(opt) {
        case 'w':
            if (!(*world = named_or_current_world(ptr)))
                return FALSE;
            break;
        case 's':
            if ((*subflag = enum2int(ptr, 0, enum_sub, "-s")) < 0)
                return FALSE;
            break;
        case 'S':
            ptime->tv_sec = PTIME_SYNC;
            break;
        case 'P':
            ptime->tv_sec = PTIME_PROMPT;
            break;
        case 'd':
            if ((*disp = enum2int(ptr, 0, enum_disp, "-d")) < 0)
                return FALSE;
            break;
        case 'n':
            *delay = FALSE;
            break;
        case '-':
            *ptime = uval.tval;
            break;
        default:  return FALSE;
        }
    }
    return TRUE;
}

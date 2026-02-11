doorganize(void)
{
    struct obj *obj, *otmp;
    register int ix, cur;
    register char let;
    char alphabet[52+1], buf[52+1];
    char qbuf[QBUFSZ];
    char allowall[2];
    const char *adj_type;

    if (!flags.invlet_constant) reassign();

    allowall[0] = ALL_CLASSES; allowall[1] = '\0';
    if (!(obj = getobj(allowall,"adjust"))) return(0);


    for (let = 'a', ix = 0;  let <= 'z';) alphabet[ix++] = let++;
    for (let = 'A', ix = 26; let <= 'Z';) alphabet[ix++] = let++;
    alphabet[52] = 0;


    for (otmp = invent; otmp; otmp = otmp->nobj)
            if (otmp != obj && !mergable(otmp,obj)) {
                if (otmp->invlet <= 'Z')
                        alphabet[(otmp->invlet) - 'A' + 26] = ' ';
                else	alphabet[(otmp->invlet) - 'a']	    = ' ';
            }


    for (ix = cur = 0; ix <= 52; ix++)
            if (alphabet[ix] != ' ') buf[cur++] = alphabet[ix];


    if(cur > 5) compactify(buf);


    for (;;) {
        sprintf(qbuf, "Adjust letter to what [%s]?",buf);
        let = yn_function(qbuf, (char *)0, '\0');
        if(index(quitchars,let)) {
            pline(Never_mind);
            return(0);
        }
        if (let == '@' || !letter(let))
                pline("Select an inventory slot letter.");
        else
                break;
    }


    adj_type = "Moving:";


    extract_nobj(obj, &invent);

    for (otmp = invent; otmp;)
            if (merged(&otmp,&obj)) {
                adj_type = "Merging:";
                obj = otmp;
                otmp = otmp->nobj;
                extract_nobj(obj, &invent);
            } else {
                if (otmp->invlet == let) {
                    adj_type = "Swapping:";
                    otmp->invlet = obj->invlet;
                }
                otmp = otmp->nobj;
            }


    obj->invlet = let;
    obj->nobj = invent;
    obj->where = OBJ_INVENT;
    invent = obj;
    reorder_invent();

    prinv(adj_type, obj, 0L);
    update_inventory();
    return(0);
}

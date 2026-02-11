parse_objectid(FILE * fp, char *name)
{
    register int    count;
    register struct subid_s *op, *nop;
    int             length;
    struct subid_s  loid[32];
    struct node    *np, *root = NULL, *oldnp = NULL;
    struct tree    *tp;

    if ((length = getoid(fp, loid, 32)) == 0) {
        print_error("Bad object identifier", NULL, CONTINUE);
        return NULL;
    }


    op = loid;
    if (!op->label) {
        if (length == 1) {
            print_error("Attempt to define a root oid", name, OBJECT);
            return NULL;
        }
        for (tp = tree_head; tp; tp = tp->next_peer)
            if ((int) tp->subid == op->subid) {
                op->label = strdup(tp->label);
                break;
            }
    }


    if (length == 1) {
        op = loid;
        np = alloc_node(op->modid);
        if (np == NULL)
            return (NULL);
        np->subid = op->subid;
        np->label = strdup(name);
        np->parent = op->label;
        return np;
    }


    for (count = 0, op = loid, nop = loid + 1; count < (length - 1);
         count++, op++, nop++) {


        if (op->label && (nop->label || (nop->subid != -1))) {
            np = alloc_node(nop->modid);
            if (np == NULL)
                return (NULL);
            if (root == NULL)
                root = np;

            np->parent = strdup(op->label);
            if (count == (length - 2)) {


                np->label = strdup(name);
            } else {
                if (!nop->label) {
                    nop->label = (char *) malloc(20 + ANON_LEN);
                    if (nop->label == NULL)
                        return (NULL);
                    sprintf(nop->label, "%s%d", ANON, anonymous++);
                }
                np->label = strdup(nop->label);
            }
            if (nop->subid != -1)
                np->subid = nop->subid;
            else
                print_error("Warning: This entry is pretty silly",
                            np->label, CONTINUE);


            if (oldnp)
                oldnp->next = np;
            oldnp = np;
        }
    }


    for (count = 0, op = loid; count < length; count++, op++) {
        if (op->label)
            free(op->label);
    }

    return root;
}

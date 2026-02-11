eat_syntax(FILE * fp, char *token, int maxtoken)
{
    int             type, nexttype;
    struct node    *np = alloc_node(current_module);
    char            nexttoken[MAXTOKEN];

    if (!np)
	return 0;

    type = get_token(fp, token, maxtoken);
    nexttype = get_token(fp, nexttoken, MAXTOKEN);
    switch (type) {
    case INTEGER:
    case INTEGER32:
    case UINTEGER32:
    case UNSIGNED32:
    case COUNTER:
    case GAUGE:
    case BITSTRING:
    case LABEL:
        if (nexttype == LEFTBRACKET) {


            np->enums = parse_enumlist(fp, &np->enums);
            nexttype = get_token(fp, nexttoken, MAXTOKEN);
        } else if (nexttype == LEFTPAREN) {


            np->ranges = parse_ranges(fp, &np->ranges);
            nexttype = get_token(fp, nexttoken, MAXTOKEN);
        }
        break;
    case OCTETSTR:
    case KW_OPAQUE:


        if (nexttype == LEFTPAREN) {
            nexttype = get_token(fp, nexttoken, MAXTOKEN);
            if (nexttype == SIZE) {
                nexttype = get_token(fp, nexttoken, MAXTOKEN);
                if (nexttype == LEFTPAREN) {
                    np->ranges = parse_ranges(fp, &np->ranges);
                    nexttype = get_token(fp, nexttoken, MAXTOKEN);
                    if (nexttype == RIGHTPAREN) {
                        nexttype = get_token(fp, nexttoken, MAXTOKEN);
                        break;
                    }
                }
            }
            print_error("Bad SIZE syntax", token, type);
            free_node(np);
            return nexttype;
        }
        break;
    case OBJID:
    case NETADDR:
    case IPADDR:
    case TIMETICKS:
    case NUL:
    case NSAPADDRESS:
    case COUNTER64:
        break;
    default:
        print_error("Bad syntax", token, type);
        free_node(np);
        return nexttype;
    }
    free_node(np);
    return nexttype;
}

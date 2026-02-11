get_attr_value(const living *stats, int attr) {
    switch (attr) {
    case STR:
        return(stats->Str);

    case DEX:
        return(stats->Dex);

    case CON:
        return(stats->Con);

    case WIS:
        return(stats->Wis);

    case CHA:
        return(stats->Cha);

    case INT:
        return(stats->Int);

    case POW:
        return(stats->Pow);
    }
    return 0;
}

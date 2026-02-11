get_idnum(char *name)
{
    int id;

    switch (get_type(name)) {
    case VOL:
	sscanf(name + 4, "%d", &id);
	break;
    default:
	sscanf(name + 5, "%d", &id);
    }

    return (id);
}

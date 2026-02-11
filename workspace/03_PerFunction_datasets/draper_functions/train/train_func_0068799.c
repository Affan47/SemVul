DEH_AmmoParseLine(deh_context_t *context, char *line, void *tag)
{
    char *variable_name, *value;
    int ivalue;
    int ammo_number;

    if (tag == NULL)
        return;

    ammo_number = ((int *) tag) - maxammo;


    if (!DEH_ParseAssignment(line, &variable_name, &value))
    {


        DEH_Warning(context, "Failed to parse assignment");
        return;
    }

    ivalue = atoi(value);


    if (!strcasecmp(variable_name, "Per ammo"))
        clipammo[ammo_number] = ivalue;
    else if (!strcasecmp(variable_name, "Max ammo"))
        maxammo[ammo_number] = ivalue;
    else
    {
        DEH_Warning(context, "Field named '%s' not found", variable_name);
    }
}

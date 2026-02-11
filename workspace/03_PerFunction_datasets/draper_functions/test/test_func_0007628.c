property_eval(PROPERTY * prop)
{
    RESULT old;
    int update;


    old.type = prop->result.type;
    old.size = prop->result.size;
    old.number = prop->result.number;
    old.string = prop->result.string != NULL ? strdup(prop->result.string) : NULL;

    DelResult(&prop->result);
    Eval(prop->compiled, &prop->result);


    update = 1;
    if (prop->result.type & R_NUMBER && old.type & R_NUMBER && prop->result.number == old.number) {
	update = 0;
    }
    if (prop->result.type & R_STRING && old.type & R_STRING && prop->result.size == old.size) {
	if (prop->result.string == NULL && old.string == NULL) {
	    update = 0;
	} else if (prop->result.string != NULL && old.string != NULL && strcmp(prop->result.string, old.string) == 0) {
	    update = 0;
	}
    }

    if (old.string)
	free(old.string);

    return update;
}

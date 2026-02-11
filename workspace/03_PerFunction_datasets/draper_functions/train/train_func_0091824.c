slapi_entry_add_valueset(Slapi_Entry *e, const char *type, Slapi_ValueSet *vs)
{
    Slapi_Value *v;

    int i= slapi_valueset_first_value(vs,&v);
    while(i!=-1) {

        slapi_entry_add_value( e, type, v);
        i= slapi_valueset_next_value(vs,i,&v);
    }

    return(0);
}

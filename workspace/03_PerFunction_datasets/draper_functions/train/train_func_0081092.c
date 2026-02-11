FindModuleRfmArray(SymbolDict sym_dict)
{
    RfmArray array;

    if (sym_dict == NULL) {
        return(NULL);
    }
    for (array = RFM_ModuleCurrent->array_list;
         array != NULL;
         array = array->next) {
        if (array->sym_dict == sym_dict) {
            return(array);
        }
    }
    return(NULL);
}

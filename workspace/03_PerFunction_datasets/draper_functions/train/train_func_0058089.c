import_symbol(int32 symbol_number)
{   sflags[symbol_number] |= IMPORT_SFLAG;
    switch(stypes[symbol_number])
    {   case GLOBAL_VARIABLE_T:
            assign_symbol(symbol_number, mv_vref--, stypes[symbol_number]);
            break;
    }
}

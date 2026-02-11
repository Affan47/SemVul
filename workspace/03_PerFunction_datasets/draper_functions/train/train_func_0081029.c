accept_import(void)
{   int32 index;

    index = symbol_index(IE.symbol_name, -1);
    sflags[index] |= USED_SFLAG;
    xref_table[IE.symbol_number] = index;

    if (!(sflags[index] & UNKNOWN_SFLAG))
    {   switch (IE.symbol_type)
        {
            case GLOBAL_VARIABLE_T:
                if (stypes[index] != GLOBAL_VARIABLE_T)
                    link_error_named(
"module (wrongly) declared this a variable:", IE.symbol_name);
                variables_map[IE.symbol_value] = svals[index];
                if (IE.symbol_value < lowest_imported_global_no)
                    lowest_imported_global_no = IE.symbol_value;
                break;
            default:
                switch(stypes[index])
                {   case ATTRIBUTE_T:
                        link_error_named(
"this attribute is undeclared within module:", IE.symbol_name);; break;
                    case PROPERTY_T:
                        link_error_named(
"this property is undeclared within module:", IE.symbol_name); break;
                    case INDIVIDUAL_PROPERTY_T:
                    case ARRAY_T:
                    case ROUTINE_T:
                    case CONSTANT_T:
                    case OBJECT_T:
                    case CLASS_T:
                    case FAKE_ACTION_T:
                        break;
                    default:
                        link_error_named(
"this was referred to as a constant, but isn't:", IE.symbol_name);
                        break;
                }
                break;
        }
    }
    else
    {   switch (IE.symbol_type)
        {
            case GLOBAL_VARIABLE_T:
                if (stypes[index] != GLOBAL_VARIABLE_T)
                    link_error_named(
                "Module tried to import a Global variable not defined here:",
                        IE.symbol_name);
                variables_map[IE.symbol_value] = 16;
                if (IE.symbol_value < lowest_imported_global_no)
                    lowest_imported_global_no = IE.symbol_value;
                break;
        }
    }
}

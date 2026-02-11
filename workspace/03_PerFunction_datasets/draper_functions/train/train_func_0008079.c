make_pointer_type_dict(TypeDict type_dict)
{
    Rsymbol_dict_table rsym_table;
    Type_dict_table    type_table;

    memset(&rsym_table, 0, sizeof(Rsymbol_dict_table));
    memset(&type_table, 0, sizeof(Type_dict_table));

    rsym_table.type = type_dict;
    switch (type_dict->type_kind) {
    case TKIND_VOID:
        rsym_table.type_attr1 = ATTR1_VOID;
        break;
    case TKIND_STRUCT:
        rsym_table.type_attr1 = ATTR1_STRUCT;
        break;
    case TKIND_UNION:
        rsym_table.type_attr1 = ATTR1_UNION;
        break;
    case TKIND_POINTER:
        rsym_table.type_attr1 = ATTR1_POINTER;
        break;
    case TKIND_ARRAY:
        rsym_table.type_attr1 = ATTR1_ARRAY;
        break;
    case TKIND_FUNC:
        rsym_table.type_attr1 = ATTR1_FUNC;
        break;
    case TKIND_BASE:
    case TKIND_ENUMERATE:
        switch (type_dict->TYPE_TYPE_DETAILS) {
        case DETAILS_SIGNED_CHAR:
            rsym_table.type_attr1 = ATTR1_SIGNED_CHAR;
            break;
        case DETAILS_UNSIGNED_CHAR:
            rsym_table.type_attr1 = ATTR1_UNSIGNED_CHAR;
            break;
        case DETAILS_SIGNED_SHORT:
            rsym_table.type_attr1 = ATTR1_SIGNED_SHORT;
            break;
        case DETAILS_UNSIGNED_SHORT:
            rsym_table.type_attr1 = ATTR1_UNSIGNED_SHORT;
            break;
        case DETAILS_SIGNED_INT:
            rsym_table.type_attr1 = ATTR1_SIGNED_INT;
            break;
        case DETAILS_UNSIGNED_INT:
            rsym_table.type_attr1 = ATTR1_UNSIGNED_INT;
            break;
        case DETAILS_SIGNED_LLONG:
            rsym_table.type_attr1 = ATTR1_SIGNED_LONG_LONG;
            break;
        case DETAILS_UNSIGNED_LLONG:
            rsym_table.type_attr1 = ATTR1_UNSIGNED_LONG_LONG;
            break;
        case DETAILS_FLOAT:
            rsym_table.type_attr1 = ATTR1_FLOAT;
            break;
        case DETAILS_DOUBLE:
            rsym_table.type_attr1 = ATTR1_DOUBLE;
            break;
        case DETAILS_LONG_DOUBLE:
            rsym_table.type_attr1 = ATTR1_LONG_DOUBLE;
            break;
        default:
            break;
        }
    default:
        break;
    }
    type_table.type_kind = TKIND_POINTER;
    type_table.TYPE_REFERRED_TYPE = type_dict;
    type_table.modify_attr = ATTR_COMPLETE;
    type_table.TYPE_RSYM = DICT_MakeRsymbol(&rsym_table);
    type_table.type_size = commonp->pointer_size;
    type_table.boundary = commonp->pointer_boundary;

    return(DICT_MakeType(&type_table));
}

print_pragma_list(RfmPragma pragma, int indent)
{
    char    *buf;
    RfmQuad  quad;

    if (pragma == NULL) {
        return;
    }

    BUFFER_CLEAR(buf);
    BUFFER_INDENT(buf, indent);
    buf += sprintf(buf, "(");
    NEW_INDENT_LINE(buf, indent + 1);
    while (pragma) {
        switch (pragma->kind) {
        case RFM_PRAGMA_ID:
            buf += sprintf(buf, "%d", pragma->pragma_id);
            NEW_INDENT_LINE(buf, indent + 1);
            break;
        case RFM_PRAGMA_CONST:
            buf += sprintf(buf, "%d", pragma->pragma_const);
            NEW_INDENT_LINE(buf, indent + 1);
            break;
        case RFM_PRAGMA_OPERAND:
            buf = PrintOperand(buf, pragma->pragma_operand);
#if 1
            if (pragma->next != NULL &&
                pragma->next->kind == RFM_PRAGMA_RANGE) {
                pragma = pragma->next;
                continue;
            }
#endif
            NEW_INDENT_LINE(buf, indent + 1);
            break;
        case RFM_PRAGMA_EXP:
            buf += sprintf(buf, "%s {", FCV_QUAD_KEYWORD);
            if (pragma->quad_list) {
                NEW_INDENT_LINE(buf, indent + 2);
            } else {
                NEW_INDENT_LINE(buf, indent + 1);
            }
            quad = pragma->quad_list;
            while (quad) {
                PrintQuad(buf, quad);
                if (quad == pragma->quad_tail) {
                    NEW_INDENT_LINE(buf, indent + 1);
                    break;
                }
                NEW_INDENT_LINE(buf, indent + 2);
                quad = quad->next;
            }
            buf += sprintf(buf, "} %% %s", FCV_QUAD_KEYWORD);
            NEW_INDENT_LINE(buf, indent + 1);
            buf = PrintOperand(buf, pragma->pragma_exp);
            buf += sprintf(buf, " %% result");
            NEW_INDENT_LINE(buf, indent + 1);
            break;
        case RFM_PRAGMA_LIST:
            print_pragma_list(pragma->pragma_list, indent + 1);
            BUFFER_CLEAR(buf);
            BUFFER_INDENT(buf, indent + 1);
            break;
        case RFM_PRAGMA_LITRL:
            buf += sprintf(buf, "<%s>", pragma->litrl_dict->string);
            NEW_INDENT_LINE(buf, indent + 1);
            break;
#if 1
        case RFM_PRAGMA_RANGE:
            pragma = print_pragma_range(buf, pragma, indent + 1);
            BUFFER_CLEAR(buf);
            BUFFER_INDENT(buf, indent + 1);
            if (pragma != NULL) {
                buf += sprintf(buf, ",");
                NEW_INDENT_LINE(buf, indent + 1);
            }
            continue;
#endif
        default:
            break;
        }
        if (pragma->next) {
            buf += sprintf(buf, ",");
            NEW_INDENT_LINE(buf, indent + 1);
        }
        pragma = pragma->next;
    }
    buf += sprintf(buf, ")");
    NEW_LINE(buf);
}

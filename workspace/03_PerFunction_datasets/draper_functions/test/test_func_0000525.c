gdb_command_string(int cmd, char *buf, int live)
{
        switch (cmd)
        {
        case GNU_PASS_THROUGH:
                sprintf(buf, "GNU_PASS_THROUGH");
                break;
        case GNU_DATATYPE_INIT:
                sprintf(buf, "GNU_DATATYPE_INIT");
                break;
        case GNU_DISASSEMBLE:
                sprintf(buf, "GNU_DISASSEMBLE");
                break;
        case GNU_GET_LINE_NUMBER:
                sprintf(buf, "GNU_GET_LINE_NUMBER");
                break;
        case GNU_GET_DATATYPE:
		if (live)
                	sprintf(buf, "GNU_GET_DATATYPE[%s]",
				pc->cur_req->name ? pc->cur_req->name : "?");
		else
			sprintf(buf, "GNU_GET_DATATYPE");
                break;
        case GNU_STACK_TRACE:
                sprintf(buf, "GNU_STACK_TRACE");
                break;
	case GNU_ALPHA_FRAME_OFFSET:
		sprintf(buf, "GNU_ALPHA_FRAME_OFFSET");
		break;
	case GNU_COMMAND_EXISTS:
                sprintf(buf, "GNU_COMMAND_EXISTS");
                break;
	case GNU_FUNCTION_NUMARGS:
                sprintf(buf, "GNU_FUNCTION_NUMARGS");
                break;
	case GNU_RESOLVE_TEXT_ADDR:
                sprintf(buf, "GNU_RESOLVE_TEXT_ADDR");
                break;
	case GNU_DEBUG_COMMAND:
                sprintf(buf, "GNU_DEBUG_COMMAND");
                break;
	case GNU_ADD_SYMBOL_FILE:
                sprintf(buf, "GNU_ADD_SYMBOL_FILE");
                break;
	case GNU_DELETE_SYMBOL_FILE:
                sprintf(buf, "GNU_DELETE_SYMBOL_FILE");
                break;
	case GNU_VERSION:
                sprintf(buf, "GNU_VERSION");
                break;
       case GNU_GET_SYMBOL_TYPE:
                sprintf(buf, "GNU_GET_SYMBOL_TYPE");
                break;
        case GNU_PATCH_SYMBOL_VALUES:
                sprintf(buf, "GNU_PATCH_SYMBOL_VALUES");
                break;
        case GNU_USER_PRINT_OPTION:
                sprintf(buf, "GNU_USER_PRINT_OPTION");
		break;
        case GNU_SET_CRASH_BLOCK:
                sprintf(buf, "GNU_SET_CRASH_BLOCK");
		break;
	case 0:
		buf[0] = NULLCHAR;
		break;
        default:
                sprintf(buf, "(?)\n");
                break;
        }

	return buf;
}

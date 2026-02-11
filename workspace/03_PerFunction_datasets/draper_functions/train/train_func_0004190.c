search_register(const Operand* op, int part, symbol_type type)
{   int  i;
    const RegisterAliasList*  ptr;

#ifdef  DEBUG_REGISTER_TABLE
    fputs(";#  Search Register : ", stdout);
    output_operand_name(op, part, type);
#endif

    if  (op == NULL)
    {   ERROR_BOPERAND;
    }

    if  (type == TYPE_UNDEC) {
	switch  (op->kind) {
	case    KIND_VAR:
	case    KIND_TEMP:
	case    KIND_CONST:
	case    KIND_ARRAY:
	    type    =   op->tbl.v->type;
	    break;
	default:
	    ERROR_UKIND;
        }
    }

    if  (type == TYPE_DOUBLE
	 || is_complex(type)) {
	type = TYPE_REAL;
    }
    if  (is_integer(type)
	 || type == TYPE_PTR) {
	type = TYPE_INT;
    }

    for (i=0; i<register_table_number; i++)
    {   if  (register_table[i].state != FREE)
        {   ptr =   register_table[i].alias;
            while   (ptr != NULL)
            {   if  (equal_operand(ptr->operand, op)
                      &&  (ptr->part == part)
                      &&  ((type == TYPE_UNDEC)
                             || (register_table[i].type == type)))
                {
#ifdef  DEBUG_REGISTER_TABLE
                    printf(" : R%d\n", i);
#endif
                    return i;
                }
	    else if (!is_complex(type)
		     && part==1
		     && ptr->operand->kind == KIND_CONST
		     && ptr->operand->tbl.c->entry == real_zero_constant_entry()) {
#ifdef  DEBUG_REGISTER_TABLE
                    printf(" : R%d\n", i);
#endif
                    return i;
                }
                ptr =   ptr->next;
            }
        }
    }

#ifdef  DEBUG_REGISTER_TABLE
    fputs(" : Not Found\n", stdout);
#endif

    return  -1;
}

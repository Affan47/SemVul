print_primary(struct i_primary *pri)
{
if(pri)
	{
	if(pri->primtype==PRIM_FUNC)
		{
		printf("PRIM: FUNCALL (%s)\n",pri->primval.funcall.name->name);
		printf("ARGS vvvvvvvvvvvv\n");
		print_explist(pri->primval.funcall.args);
		printf("ARGS ^^^^^^^^^^^^\n");
		}
	else
	if(pri->primtype==PRIM_CONCAT)
		{
		print_concat(pri->primval.concat.count,
			     pri->primval.concat.exp);
		}
	else
	if(pri->primtype==PRIM_SYMBIT)
		{
		printf("PRIM: SYMBIT (%s)\n",pri->primval.symbit.sym->name);
		printf("vvvvvvvvvvvv\n");
		print_primary(pri->primval.symbit.bitnum);
		printf("^^^^^^^^^^^^\n");
		}
	else
	if(pri->primtype==PRIM_SYMRANGE)
		{
		printf("PRIM: RANGE (%s)\n",pri->primval.symrange.sym->name);
		printf("msb vvvvvvvvvvvv\n");
		print_primary(pri->primval.symrange.msb);
		printf("msb ^^^^^^^^^^^^\n");
		printf("lsb vvvvvvvvvvvv\n");
		print_primary(pri->primval.symrange.lsb);
		printf("lsb ^^^^^^^^^^^^\n");
		}
	else
	if(pri->primtype==PRIM_SYMBOL)
		{
		printf("PRIM: SYMBOL (%s)\n",pri->primval.symbol->name);
		}
	else
	if(pri->primtype==PRIM_EXP)
		{
		printf("PRIM: EXPRESSION\n");
		}
	else
	if(pri->primtype==PRIM_MINTYPMAX)
		{
		printf("PRIM: MINTYPMAX\n");
		}
	else
	if(pri->primtype==PRIM_NUMBER)
		{
		if(pri->primval.number)
		{
		if(pri->primval.number->numtype==NV_IVAL)
			{
			printf("PRIM: %d\n",pri->primval.number->num.ival);
			}
			else if(pri->primval.number->numtype==NV_RVAL)
			{
			printf("PRIM: %.16g\n",pri->primval.number->num.rval);
			}
			else
			{
			printf("PRIM: %d %s\n",pri->primval.number->num.base.len,
				pri->primval.number->num.base.val);
			}
		}
		else
		{
		printf("NON-NUMBER PRIMARY\n");
		};
		}
		else
		{
		printf("YET UNSUPPORTED PRIMARY\n");
		}
	}
	else
	{
	printf("NULL PRIMARY\n");
	}
}

GenRulePrototypes( FILE *f, Junction *p )
#else
GenRulePrototypes( f, p )
FILE *f;
Junction *p;
#endif
{
	int i;

	i = 1;
	while ( p!=NULL )
	{
		if ( p->ret != NULL )
		{
	if ( hasMultipleOperands(p->ret) )
			{
				DumpRetValStruct(f, p->ret, i);
			}
			fprintf(f, "\n#ifdef __USE_PROTOS\n");
	if ( hasMultipleOperands(p->ret) )
			{
				fprintf(f, "extern struct _rv%d", i);
			}
			else
			{
				fprintf(f, "extern ");
				DumpType(p->ret, f);
			}
			fprintf(f, " %s%s(", RulePrefix, p->rname);
			DumpANSIFunctionArgDef(f,p,1 );
			fprintf(f, ";\n");
			fprintf(f, "#else\n");
	if ( hasMultipleOperands(p->ret) )
			{
				fprintf(f, "extern struct _rv%d", i);
			}
			else
			{
				fprintf(f, "extern ");
				DumpType(p->ret, f);
			}
			fprintf(f, " %s%s();\n", RulePrefix, p->rname);
			fprintf(f, "#endif\n");
		}
		else
		{
			fprintf(f, "\n#ifdef __USE_PROTOS\n");
			fprintf(f, "void %s%s(", RulePrefix, p->rname);
			DumpANSIFunctionArgDef(f,p, 1  );
			fprintf(f, ";\n");
#ifdef OLD
			if ( p->pdecl != NULL || GenAST )
			{
				if ( GenAST ) {
					fprintf(f, "AST **%s",(p->pdecl!=NULL)?",":"");
				}
				if ( p->pdecl!=NULL ) fprintf(f, "%s", p->pdecl);
			}
			else fprintf(f, "void");
			fprintf(f, ");\n");
#endif
			fprintf(f, "#else\n");
			fprintf(f, "extern void %s%s();\n", RulePrefix, p->rname);
			fprintf(f, "#endif\n");
		}
		i++;
		p = (Junction *)p->p2;
	}
}

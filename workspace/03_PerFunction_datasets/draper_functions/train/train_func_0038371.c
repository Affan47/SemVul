GenRuleMemberDeclarationsForCC( FILE *f, Junction *q )
#else
GenRuleMemberDeclarationsForCC( f, q )
FILE *f;
Junction *q;
#endif
{
	Junction *p = q;
	int i;

	fprintf(f, "private:\n");


	fprintf(f, "\tvoid zzdflthandlers( int _signal, int *_retsignal );\n\n");

	fprintf(f, "public:\n");


	i = 1;
	while ( p!=NULL )
	{
		if ( p->ret != NULL )
		{
	if ( hasMultipleOperands(p->ret) )
			{
				DumpRetValStruct(f, p->ret, i);
			}
		}
		i++;
		p = (Junction *)p->p2;
	}


	fprintf(f, "\t%s(ANTLRTokenBuffer *input);\n", CurrentClassName);


	i = 1;
	p = q;
	while ( p!=NULL )
	{
		if ( p->ret != NULL )
		{
	if ( hasMultipleOperands(p->ret) )
			{
				fprintf(f, "\tstruct _rv%d", i);
			}
			else
			{
				fprintf(f, "\t");
				DumpType(p->ret, f);
			}
			fprintf(f, " %s%s(",RulePrefix,p->rname);
			DumpANSIFunctionArgDef(f,p, 1  );
			fprintf(f, ";\n");
#ifdef OLD
			if ( p->pdecl != NULL || GenAST )
			{
				if ( GenAST ) fprintf(f, "ASTBase **%s",(p->pdecl!=NULL)?",":"");
				if ( p->pdecl!=NULL ) fprintf(f, "%s", p->pdecl);
			}
			fprintf(f, ");\n");
#endif
		}
		else
		{
			fprintf(f, "\tvoid %s%s(",RulePrefix,p->rname);
			DumpANSIFunctionArgDef(f,p, 1 );
			fprintf(f, ";\n");
#ifdef OLD
			if ( p->pdecl != NULL || GenAST )
			{
				if ( GenAST ) fprintf(f, "ASTBase **%s",(p->pdecl!=NULL)?",":"");
				if ( p->pdecl!=NULL ) fprintf(f, "%s", p->pdecl);
			}
			fprintf(f, ");\n");
#endif
		}
		i++;
		p = (Junction *)p->p2;
	}
}

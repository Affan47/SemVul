inlineScan(InlineScanState *iss)
{
#if LOG
    printf("ExpStatement::inlineScan(%s)\n", toChars());
#endif
    if (exp)
    {
        exp = exp->inlineScan(iss);


        if (exp && exp->op == TOKcall)
        {
            CallExp *ce = (CallExp *)exp;
            if (ce->e1->op == TOKvar)
            {
                VarExp *ve = (VarExp *)ce->e1;
                FuncDeclaration *fd = ve->var->isFuncDeclaration();

                if (fd && fd != iss->fd && fd->canInline(0, 0, 1))
                {
                    Statement *s;
                    fd->expandInline(iss, NULL, ce->arguments, &s);
                    return s;
                }
            }
        }
    }
    return this;
}

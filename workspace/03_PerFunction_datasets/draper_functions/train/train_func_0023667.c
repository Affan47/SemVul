ctfeCompile(CompiledCtfeFunction *ccf)
{
#if LOGCOMPILE
    printf("%s SwitchStatement::ctfeCompile\n", loc.toChars());
#endif
    ccf->onExpression(condition);


    for (size_t i = 0; i < cases->dim; i++)
    {
        ccf->onExpression((*cases)[i]->exp);
    }
    if (body)
        body->ctfeCompile(ccf);
}

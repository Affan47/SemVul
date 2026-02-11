blockExit(bool mustNotThrow)
{

    int result = BEfallthru;
    Statement *slast = NULL;
    for (size_t i = 0; i < statements->dim; i++)
    {   Statement *s = (*statements)[i];
        if (s)
        {


            if (global.params.warnings && result & BEfallthru && slast)
            {
                slast = slast->last();
                if (slast && (slast->isCaseStatement() || slast->isDefaultStatement()) &&
                             (s->isCaseStatement() || s->isDefaultStatement()))
                {

                    CaseStatement *sc = slast->isCaseStatement();
                    DefaultStatement *sd = slast->isDefaultStatement();
                    if (sc && (!sc->statement->hasCode() || sc->statement->isCaseStatement()))
                        ;
                    else if (sd && (!sd->statement->hasCode() || sd->statement->isCaseStatement()))
                        ;
                    else
                        s->error("switch case fallthrough - use 'goto %s;' if intended",
                            s->isCaseStatement() ? "case" : "default");
                }
            }

            if (!(result & BEfallthru) && !s->comeFrom())
            {
                if (s->blockExit(mustNotThrow) != BEhalt && s->hasCode())
                    s->warning("statement is not reachable");
            }
            else
            {
                result &= ~BEfallthru;
                result |= s->blockExit(mustNotThrow);
            }
            slast = s;
        }
    }
    return result;
}

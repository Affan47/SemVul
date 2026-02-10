parseTemplateArgument()
{

    Objects *tiargs = new Objects();
    Type *ta;
    switch (token.value)
    {
        case TOKidentifier:
            ta = new TypeIdentifier(token.loc, token.ident);
            goto LabelX;

        case TOKvector:
            ta = parseVector();
            goto LabelX;

        case BASIC_TYPES_X(ta):
            tiargs->push(ta);
            nextToken();
            break;

        case TOKint32v:
        case TOKuns32v:
        case TOKint64v:
        case TOKuns64v:
        case TOKfloat32v:
        case TOKfloat64v:
        case TOKfloat80v:
        case TOKimaginary32v:
        case TOKimaginary64v:
        case TOKimaginary80v:
        case TOKnull:
        case TOKtrue:
        case TOKfalse:
        case TOKcharv:
        case TOKwcharv:
        case TOKdcharv:
        case TOKstring:
        case TOKfile:
        case TOKline:
        case TOKmodulestring:
        case TOKfuncstring:
        case TOKprettyfunc:
        case TOKthis:
        {
            Expression *ea = parsePrimaryExp();
            tiargs->push(ea);
            break;
        }

        default:
            error("template argument expected following !");
            break;
    }
    if (token.value == TOKnot)
    {
        TOK tok = peekNext();
        if (tok != TOKis && tok != TOKin)
            error("multiple ! arguments are not allowed");
    }
    return tiargs;
}

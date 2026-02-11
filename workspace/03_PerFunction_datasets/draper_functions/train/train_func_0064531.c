ajStrTokenStepS(AjPStrTok token, const AjPStr strdelim)
{
    if(!token)
	return ajFalse;

    ajStrAssignS(&token->Delim, strdelim);

    return ajStrTokenStep(token);
}

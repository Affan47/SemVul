cpp_token_len (const cpp_token *token)
{
  unsigned int len;

  switch (TOKEN_SPELL (token))
    {
    default:		len = 4;				break;
    case SPELL_LITERAL:	len = token->val.str.len;		break;
    case SPELL_IDENT:	len = NODE_LEN (token->val.node);	break;
    }

  return len;
}

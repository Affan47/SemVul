Pchannel (struct chnlist **chlip)
{
int t;
int md = 0, ld = 0, mn = 0, tn = 0;
const char *tmp = 0;
struct channel *chan;

    t = yylex();
    if (t == T_begin) {
	tesc_emerg (CHN_MSG, 0,
			"line %d: missing label for channel\n", yylineno);
	tmp = "<no label specified>";
    }
    else if (t != T_STRING) {
	tesc_emerg (CHN_MSG, MF_ERR, "line %d: syntax error\n", yylineno);
	return 1;
    } else {
	tmp = make_string (yytext, yyleng, 1);
        if (yylex() != T_begin) {
	    tesc_emerg (CHN_MSG, MF_ERR, "line %d: '{' expected\n", yylineno);
	    return 1;
	}
    }


    *chlip = (struct chnlist *) sec_malloc (sizeof(struct chnlist));
    (*chlip)->next = 0;
    chan = &(*chlip)->channel;
    chan->enabled = 0;
    chan->name = 0;
    chan->log = 0;
    chan->msg = 0;
    chan->type = "";
    chan->method.type = -1;
    chan->method.str = 0;
    chan->method.data = 0;


    chan->name = tmp;

    while ((t = yylex()) != T_EOF)
	switch (t) {
	    case T_end :
		if (tn == 0) {
		    tesc_emerg (CHN_MSG, MF_ERR,
			"line %d: no channel type declared\n", yylineno);
		    return 1;
		}
		if (mn == 0) {
		    tesc_emerg (CHN_MSG, MF_ERR,
			"line %d: no channel method declared\n", yylineno);
		    return 1;
		}
		return 0;
	    case T_type :
		if (Ptype (&chan->type))
		    tesc_emerg (CHN_MSG, MF_ERR,
			"line %d: error in channel type definition\n",
								yylineno);
		else if (tn++)
		    tesc_emerg (CHN_MSG, 0,
			"line %d: channel type redefined\n", yylineno);
		break;
	    case T_method :
		if (Pmethod (&chan->method))
		    tesc_emerg (CHN_MSG, MF_ERR,
			"line %d: error in channel method definition\n",
								yylineno);
		else if (mn++)
		    tesc_emerg (CHN_MSG, 0,
			"line %d: channel method redefined\n", yylineno);
		break;
	    case T_msg :
		if (Pmsg (&chan->msg))
		    tesc_emerg (CHN_MSG, MF_ERR,
			"line %d: error in channel message definition\n",
								yylineno);
		else if (md++)
		    tesc_emerg (CHN_MSG, 0,
			"line %d: channel message redefined\n", yylineno);
		break;
	    case T_log :
		if (Plog (&chan->log))
		    tesc_emerg (CHN_MSG, MF_ERR,
			"line %d: error in channel logfile specification\n",
								yylineno);
		else if (ld++)
		    tesc_emerg (CHN_MSG, 0,
			"line %d: channel logfile redefined\n", yylineno);
		break;
	    default:
		tesc_emerg (CHN_MSG, MF_ERR,
				"line %d: unexpected element\n", yylineno);
		break;
	}

    tesc_emerg (CHN_MSG, MF_ERR, "EOF while parsing channel definition\n");
    return 1;
}

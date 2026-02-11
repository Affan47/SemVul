addarg(trpp, rp, tok, lenp, notok)
syntaxtree **trpp;
redirectlist *rp;
char *tok;
int *lenp, notok;
{
	syntaxtree *tmptr;
	int i, n, id, type;

	type = rp -> type;
	rp -> type = 0;
	if (!tok) tok = rp -> filename;

	if ((*trpp) -> flags & ST_NODE) {
		syntaxerrno = ER_UNEXPTOK;
		return(-1);
	}

	if (!*lenp) {
		if (type && notok) {
			syntaxerrno = ER_UNEXPTOK;
			return(-1);
		}
		rp -> type = type;
		return(0);
	}
	tok[*lenp] = '\0';
	*lenp = 0;

	if (!type) {
		id = getstatid(tmptr = parentstree(*trpp));
		type = (id >= 0) ? statementlist[id].type : 0;

		if ((type & STT_NEEDIDENT) && tmptr == getparent(*trpp))
			;
		else if (!((*trpp) -> comm) || ischild((*trpp) -> comm)) {
			for (i = 0; i < STATEMENTSIZ; i++)
			if (!strcommcmp(tok, statementlist[i].ident)) {
				n = parsestatement(trpp, i, id + 1, type);
				if (!n) continue;
				else if (n > 0) return(0);

				syntaxerrno = ER_UNEXPTOK;
				return(-1);
			}
		}
		if (isstatement((*trpp) -> comm)) {
			syntaxerrno = ER_UNEXPTOK;
			return(-1);
		}

		*trpp = _addarg(*trpp, tok);
	}
	else if (redirect(*trpp, rp -> fd, tok, type) < 0) return(-1);

	return(0);
}

add_new_macro(const char *trig, const char *bind, const hookvec_t *hook,
    const char *hargs, const char *body, int pri, int prob, attr_t attr,
    int invis, int mflag)
{
    Macro *new;
    int error = 0;

    if (!(new = (Macro *) MALLOC(sizeof(struct Macro)))) {
        eprintf("add_new_macro: not enough memory");
        return 0;
    }
    new->numnode = new->trignode = new->hashnode = NULL;
    new->flags = MACRO_TEMP;
    new->prog = new->exprprog = NULL;
    new->name = STRDUP("");
    (new->body = CS(Stringnew(body, -1, 0)))->links++;
    new->expr = NULL;
    new->bind = STRDUP(bind);
    new->keyname = STRDUP("");
    if (hook) {
	new->flags |= MACRO_HOOK;
	new->hook = *hook;
    } else {
	VEC_ZERO(&new->hook);
    }
    error += !init_pattern(&new->trig, trig, mflag);
    error += !init_pattern(&new->hargs, hargs, mflag);
    init_pattern_str(&new->wtype, NULL);
    new->world = NULL;
    new->pri = pri;
    new->prob = prob;
    new->attr = attr;
    new->nsubattr = 0;
    new->subattr = NULL;
    new->shots = 0;
    new->invis = invis;
    new->fallthru = FALSE;
    new->quiet = FALSE;
    new->builtin = NULL;
    new->used[USED_NAME] = new->used[USED_TRIG] =
	new->used[USED_HOOK] = new->used[USED_KEY] = 0;

    if (!error)
	return add_numbered_macro(new, 0, 0, NULL);
    nuke_macro(new);
    return 0;
}

_GDraw_DoBiText(GWindow gw, int32 x, int32 y,
	const unichar_t *text, int32 cnt, FontMods *mods, Color col,
	enum text_funcs drawit, struct tf_arg *arg, int start) {
    GBiText bd;
    unichar_t btext[MAXBI];
    uint8 level[MAXBI], override[MAXBI];
    uint16 type[MAXBI];
    unichar_t *orig[MAXBI];
    int32 width;

    if ( cnt==-1 ) cnt = u_strlen(text);
    if ( cnt<MAXBI-1 ) {
	bd.text = btext;
	bd.level = level;
	bd.override = override;
	bd.type = type;
	bd.original = orig;
    } else {
	++cnt;
	bd.text = malloc(cnt*sizeof(unichar_t));
	bd.level = malloc(cnt*sizeof(uint8));
	bd.override = malloc(cnt*sizeof(uint8));
	bd.type = malloc(cnt*sizeof(uint16));
	bd.original = malloc(cnt*sizeof(unichar_t *));
	--cnt;
    }
    bd.len = cnt;
    bd.base_right_to_left = start==-1 ? 1 : 0;
    GDrawBiText1(&bd, text, cnt);
    GDrawBiText2(&bd, 0, bd.len);

    width = _GDraw_DoText(gw,x,y,bd.text,bd.len,mods,col,drawit,arg);
    if ( arg!=NULL ) {
	if (arg->last==NULL )
	    arg->last = (unichar_t *) text + cnt;
	else
	    arg->last = bd.original[arg->last-bd.text];
    }
    if ( cnt>=MAXBI ) {
	free(bd.text); free(bd.level); free(bd.override); free(bd.type);
	free(bd.original);
    }
return( width );
}

GDrawDrawBiText8(GWindow gw, int32 x, int32 y,
	const char *text, int32 cnt, FontMods *mods, Color col) {
    int ret;
    struct tf_arg arg;

#ifndef _NO_LIBPANGO
    if ( gw->usepango )
return( _GXPDraw_DoText8(gw,x,y,text,cnt,mods,col,tf_drawit,&arg));
    else
#endif
    if (( ret = GDrawIsAllLeftToRight8(text,cnt))==1 ) {
	memset(&arg,'\0',sizeof(arg));
return( _GDraw_DoText8(gw,x,y,text,cnt,mods,col,tf_drawit,&arg));
    } else {
	unichar_t *temp = cnt==-1 ? utf82u_copy(text): utf82u_copyn(text,cnt);
	int width;
	width = _GDraw_DoBiText(gw,x,y,temp,-1,mods,col,tf_drawit,NULL,ret);
	free(temp);
return( width );
    }
}

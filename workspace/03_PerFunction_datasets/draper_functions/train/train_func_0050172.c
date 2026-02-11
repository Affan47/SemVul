GDrawGetBiText8Width(GWindow gw, const char *text, int len, int32 cnt, FontMods *mods) {
    int ret;
    struct tf_arg arg;

#ifndef _NO_LIBPANGO
    if ( gw->usepango )
return( _GXPDraw_DoText8(gw,0,0,text,cnt,mods,0x0,tf_width,&arg));
    else
#endif
    if (( ret = GDrawIsAllLeftToRight8(text,cnt))==1 ) {
	memset(&arg,'\0',sizeof(arg));
return( _GDraw_DoText8(gw,0,0,text,cnt,mods,0x0,tf_width,&arg));
    } else {
	unichar_t *temp = cnt==-1 ? utf82u_copy(text): utf82u_copyn(text,cnt);
	int width;
	width = _GDraw_DoBiWidth(gw,temp,u_strlen(temp),u_strlen(temp),mods,tf_width,ret);
	free(temp);
return( width );
    }
}

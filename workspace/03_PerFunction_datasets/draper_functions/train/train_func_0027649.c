buildin_mapannounce_sub(struct block_list *bl,va_list ap)
{
	char *str;
	size_t len;
	int color;
	int flag;
	int type,size,align,pos_y;

	nullpo_retr(0, bl);

	str   = va_arg(ap,char *);
	len   = va_arg(ap,size_t);
	flag  = va_arg(ap,int);
	color = va_arg(ap,int);
	type  = va_arg(ap,int);
	size  = va_arg(ap,int);
	align = va_arg(ap,int);
	pos_y = va_arg(ap,int);

	if(color)
		clif_announce(bl,str,len,(unsigned int)color,type,size,align,pos_y,flag|3);
	else
		clif_GMmessage(bl,str,len,flag|3);
	return 0;
}

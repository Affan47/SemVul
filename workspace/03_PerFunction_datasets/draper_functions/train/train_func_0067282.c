PickWindow(Jax *jax)
{
	Cursor plus_cursor;

	plus_cursor=XCreateFontCursor(jax->d,XC_gumby);
	XGrabButton(jax->d,
			1,
			AnyModifier,
			JAXdefaultrootwin(jax),
			True,
			ButtonPressMask,
			GrabModeAsync,GrabModeAsync,
			None,
			plus_cursor);
	grabwin=0;
	JAXeventloop(jax);
	XUngrabButton(jax->d,
			1,
			AnyModifier,
			JAXdefaultrootwin(jax));
	XFreeCursor(jax->d,plus_cursor);

	Printf("grabwin=%08x\n",(unsigned)grabwin);
	freeAllX(&xch,NULL,&wname);
	wname=windowName(jax->d,grabwin);
	XGetClassHint(jax->d,grabwin,&xch);
	{
		int x,y,h,w;

		h=JAXstringfullheight(jax)+2;
		w=GUI_W-name_w;
		x=MAX_SCALE_W+name_w;

		y=0;
		deleteHS(wname_hs);
		Printf("wname=%s\n",wname);
		wname_hs=newHS(x,y,w,h,LEFT,LABEL,(wname?wname:".*"),NULL,NULL);
		y+=h;
		deleteHS(res_hs);
		Printf("xch.res_name=%s\n",xch.res_name);
		res_hs=newHS(x,y,w,h,LEFT,LABEL,xch.res_name,NULL,NULL);
		y+=h;
		deleteHS(class_hs);
		Printf("xch.res_class=%s\n",xch.res_class);
		class_hs=newHS(x,y,w,h,LEFT,LABEL,xch.res_class,NULL,NULL);

		jax->xe.xexpose.count=-1;
		jax->xe.xexpose.x=x;
		jax->xe.xexpose.y=0;
		jax->xe.xexpose.width=w;
		jax->xe.xexpose.height=y+h;
		handle_expose(jax);
	}
}

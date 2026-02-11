MKDMakeActive(MathKernDlg *mkd,CharView *cv) {
    GRect r;
    int i;

    if ( mkd==NULL )
return;
    for ( i=0; i<4; ++i )
	(&mkd->cv_topright)[i].inactive = true;
    cv->inactive = false;
    GDrawSetUserData(mkd->gw,cv);
    GDrawSetUserData(mkd->cvparent_w,cv);
    for ( i=0; i<4; ++i )
	GDrawRequestExpose((&mkd->cv_topright)[i].v,NULL,false);
    GDrawGetSize(mkd->gw,&r);
    r.x = 0;
    r.y = 0;
    r.height = mkd->fh+10;
    GDrawRequestExpose(mkd->cvparent_w,&r,false);
}

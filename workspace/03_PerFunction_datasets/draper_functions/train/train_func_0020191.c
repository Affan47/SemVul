GListFit(GList *gl) {
    int bp = GBoxBorderWidth(gl->g.base,gl->g.box);
    GRect inner, outer;

    GListGetDesiredSize(&gl->g,&outer,&inner);
    if ( gl->g.r.width==0 )
	gl->g.r.width = outer.width;
    if ( gl->g.r.height==0 )
	gl->g.r.height = outer.height;
    gl->g.inner = gl->g.r;
    gl->g.inner.x += bp; gl->g.inner.y += bp;
    gl->g.inner.width -= 2*bp; gl->g.inner.height -= 2*bp;
    GListCheckSB(gl);
}

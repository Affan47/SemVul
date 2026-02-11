GMenuChangeSelection(struct gmenu *m, int newsel,GEvent *event) {
    int old=m->line_with_mouse;

    if ( old==newsel )
return;
    if ( newsel==m->mcnt )
return;

    if ( m->child!=NULL ) {
	GMenuDestroy(m->child);
	m->child = NULL;
    }
    UnsetInitialPress(m);
    m->line_with_mouse = newsel;
    if ( newsel!=-1 )
	m->mi[newsel].ti.selected = true;
    if ( old!=-1 )
	m->mi[old].ti.selected = false;

    if ( newsel==old+1 && old!=-1 ) {
	GMenuDrawLines(m,old,2);
    } else if ( old==newsel+1 && newsel!=-1 ) {
	GMenuDrawLines(m,newsel,2);
    } else {
	if ( newsel!=-1 )
	    GMenuDrawLines(m,newsel,1);
	if ( old!=-1 )
	    GMenuDrawLines(m,old,1);
    }
    if ( newsel!=-1 ) {
	if ( m->mi[newsel].moveto!=NULL )
	    (m->mi[newsel].moveto)(m->owner,&m->mi[newsel],event);
	if ( m->mi[newsel].sub!=NULL )
	    m->child = GMenuCreateSubMenu(m,m->mi[newsel].sub,
		    m->disabled || m->mi[newsel].ti.disabled);
    }
}

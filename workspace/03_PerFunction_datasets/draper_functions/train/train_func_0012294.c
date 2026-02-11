buildmenu() {
    WidgetKit& wk = *WidgetKit::instance();
    const LayoutKit& lk = *LayoutKit::instance();
    int i;
    Coord maxwidth = 0;
    Coord tempwid;
    for (i = 0; i < _obs->maxvalue(); i++) {
	if ((tempwid = wk.font()->width(_obs->labelvalue(i).string(),
					_obs->labelvalue(i).length()))
	    > maxwidth)
	    maxwidth = tempwid;
    }
    _enumobs = new EnumObserver(_obs, "", maxwidth);
    _menu = wk.menubar();
    MenuItem* mbi = wk.menubar_item(_enumobs);
    mbi->menu(wk.pullright());
    Action* action1;
    Action* action2;
    for (i = 0; i < _obs->maxvalue(); i++) {
	action1 = new EnumActionCallback(MenuEnumEditor)(
	    this, &MenuEnumEditor::edit, _obs->labelvalue(i)
	);
	action2 = _macro ? _macro->action(i) : nil;
	MenuItem* mi = wk.menu_item(lk.overlay(
	    lk.vcenter(lk.hspace(maxwidth)),
	    lk.vcenter(wk.label(_obs->labelvalue(i)))));
	mbi->menu()->append_item(mi);
	mi->action(new Macro(action1, action2));
    }
    _menu->append_item(mbi);
    return lk.hfixed(_menu, maxwidth+20);
}

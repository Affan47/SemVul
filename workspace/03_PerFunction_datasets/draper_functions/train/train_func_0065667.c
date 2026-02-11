Init (GraphicComp* comp) {
    if (GetWindow() == nil) {
	ManagedWindow* w = new ApplicationWindow(this);
	SetWindow(w);
	Style* s = new Style(Session::instance()->style());
	s->alias("IdrawEditor");
	w->style(s);
    }

    _comp = (comp == nil) ? (new IdrawComp) : comp;
    _keymap = new KeyMap;
    _curCtrl = new ControlState;
    _selection = new Selection;
    _tray = new Tray;

    InitStateVars();
    InitViewer();

    Insert(new Frame(Interior()));
    GetKeyMap()->Execute(CODE_SELECT);
}

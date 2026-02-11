MomentaryUseTool (const char* keyCode, Event& e) {
    Tool* curTool= _editor->GetCurTool();
    const char* origCode = curTool->GetControlInfo()->GetKeyCode();
    KeyMap* keymap = _editor->GetKeyMap();

    if (strcmp(origCode, keyCode) == 0) {
	UseTool(CurTool(), e);
    } else {
	keymap->Execute(keyCode);
	UseTool(CurTool(), e);
	keymap->Execute(origCode);
    }
}

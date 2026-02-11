specKey(int keyIndex)
{
    switch (keyIndex) {
        case KEY_SWITCH:
            if (!getLevel()->isActing()) {
                getLevel()->switchFish();
            }
            break;
        case KEY_SAVE:
            if (!getLevel()->isActing()) {
                getLevel()->action_save();
            }
            break;
        case KEY_LOAD:
            if (!getLevel()->isShowing()) {
                getLevel()->action_load();
            }
            break;
        case KEY_RESTART:
            getLevel()->interruptShow();
            getLevel()->action_restart(1);
            break;
        case KEY_UNDO:
            if (!getLevel()->isShowing()) {
                getLevel()->action_undo(1);
            }
            break;
        case KEY_REDO:
            if (!getLevel()->isShowing()) {
                getLevel()->action_undo(-1);
            }
            break;
        case KEY_SHOW_STEPS:
            toggleParam("show_steps");
            break;
        default:
            GameInput::specKey(keyIndex);
    }
}

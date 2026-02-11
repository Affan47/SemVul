identifyMoveAction (QKeyEvent * event, bool pressed)
{
    bool result = false;
    if (! event->isAutoRepeat()) {
        QKeySequence keystroke (event->key() + event->modifiers());
        result = true;

        if ((ACTION ("move_left"))->shortcuts().contains(keystroke)) {
            game->kbControl (LEFT, pressed);
        }
        else if ((ACTION ("move_right"))->shortcuts().contains(keystroke)) {
            game->kbControl (RIGHT, pressed);
        }
        else if ((ACTION ("move_up"))->shortcuts().contains(keystroke)) {
            game->kbControl (UP, pressed);
        }
        else if ((ACTION ("move_down"))->shortcuts().contains(keystroke)) {
            game->kbControl (DOWN, pressed);
        }
        else {
            result = false;
        }
    }
    return result;
}

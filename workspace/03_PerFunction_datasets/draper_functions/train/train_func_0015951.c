joyUp (uint8_t joystick, uint8_t button)
{
    if ( !gameIsOver () )
    {
        getLeftPlayer ()->joyUp (joystick, button);
        getRightPlayer ()->joyUp (joystick, button);
    }
}

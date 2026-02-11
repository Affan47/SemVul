getPlayerControls (IPlayer::PlayerSide player)
{
    const int playerIndex = static_cast<int> (player);
    Options::PlayerControls playerControls;
    std::string sectionName (k_PlayersName[playerIndex] + "-controls");
    playerControls.controlsType = static_cast<ControlsType> (
        getIntegerValue (sectionName, "type",
                         static_cast<int> (KeyboardControls)));

    playerControls.keyboard.moveLeft =
        getIntegerValue (sectionName, "KeyMoveLeft",
                         k_PlayersControls[playerIndex][0]);
    playerControls.keyboard.moveRight =
        getIntegerValue (sectionName, "KeyMoveRight",
                         k_PlayersControls[playerIndex][1]);
    playerControls.keyboard.pushDown =
        getIntegerValue (sectionName, "KeyPushDown",
                         k_PlayersControls[playerIndex][2]);
    playerControls.keyboard.rotateClockwise =
        getIntegerValue (sectionName, "KeyRotateCW",
                         k_PlayersControls[playerIndex][3]);
    playerControls.keyboard.rotateCounterClockwise =
        getIntegerValue (sectionName, "KeyRotateCCW",
                         k_PlayersControls[playerIndex][4]);

    playerControls.joystick.index =
        getIntegerValue (sectionName, "JoyIndex", 0);
    playerControls.joystick.moveLeft =
        getIntegerValue (sectionName, "JoyMoveLeft", -1);
    playerControls.joystick.moveRight =
        getIntegerValue (sectionName, "JoyMoveRight", 1);
    playerControls.joystick.pushDown =
        getIntegerValue (sectionName, "JoyPushDown", 2);
    playerControls.joystick.rotateClockwise =
        getIntegerValue (sectionName, "JoyRotateCW", 0);
    playerControls.joystick.rotateCounterClockwise =
        getIntegerValue (sectionName, "JoyRotateCCW", 1);


    return playerControls;
}

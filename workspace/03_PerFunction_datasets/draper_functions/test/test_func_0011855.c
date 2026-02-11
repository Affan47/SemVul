HandleAuraModIncreaseSwimSpeed(bool , bool Real)
{

    if (!Real)
        return;

    GetTarget()->UpdateSpeed(MOVE_SWIM, true);
}

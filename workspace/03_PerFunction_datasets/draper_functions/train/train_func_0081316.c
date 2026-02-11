CubePosition(const int crawford_game, const int cube_use,
             const int doubled, const int cube_owner, int fClockwise, int *px, int *py, int *porient)
{
    if (crawford_game || !cube_use) {

        if (px)
            *px = NO_CUBE;
        if (py)
            *py = NO_CUBE;
        if (porient)
            *porient = -1;
    } else if (doubled) {
        if (px)
            *px = (doubled > 0) ? CUBE_RIGHT_X : CUBE_LEFT_X;
        if (py)
            *py = CUBE_CENTRE_Y;
        if (porient)
            *porient = doubled;
    } else {
        if (px) {
            if (fClockwise)
                *px = BOARD_WIDTH - (BEAROFF_INSIDE + CUBE_TRAY_X);
            else
                *px = CUBE_TRAY_X;
        }
        if (py)
            *py = (cube_owner < 0) ? CUBE_OWN_1_Y : (cube_owner == 0) ? CUBE_CENTRE_Y : CUBE_OWN_0_Y;
        if (porient)
            *porient = cube_owner;
    }

}

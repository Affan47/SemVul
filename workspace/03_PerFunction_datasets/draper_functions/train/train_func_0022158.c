V_DrawMouseSpeedBox(int speed)
{
    extern int usemouse;
    int bgcolor, bordercolor, red, black, white, yellow;
    int box_x, box_y;
    int original_speed;
    int redline_x;
    int linelen;


    bgcolor = I_GetPaletteIndex(0x77, 0x77, 0x77);
    bordercolor = I_GetPaletteIndex(0x55, 0x55, 0x55);
    red = I_GetPaletteIndex(0xff, 0x00, 0x00);
    black = I_GetPaletteIndex(0x00, 0x00, 0x00);
    yellow = I_GetPaletteIndex(0xff, 0xff, 0x00);
    white = I_GetPaletteIndex(0xff, 0xff, 0xff);


    if (!usemouse || fabs(mouse_acceleration - 1) < 0.01)
    {
        return;
    }


    box_x = SCREENWIDTH - MOUSE_SPEED_BOX_WIDTH - 10;
    box_y = 15;

    V_DrawFilledBox(box_x, box_y,
                    MOUSE_SPEED_BOX_WIDTH, MOUSE_SPEED_BOX_HEIGHT, bgcolor);
    V_DrawBox(box_x, box_y,
              MOUSE_SPEED_BOX_WIDTH, MOUSE_SPEED_BOX_HEIGHT, bordercolor);


    redline_x = MOUSE_SPEED_BOX_WIDTH / 3;


    if (speed < mouse_threshold)
    {
        original_speed = speed;
    }
    else
    {
        original_speed = speed - mouse_threshold;
        original_speed = (int) (original_speed / mouse_acceleration);
        original_speed += mouse_threshold;
    }


    linelen = (original_speed * redline_x) / mouse_threshold;


    if (linelen > MOUSE_SPEED_BOX_WIDTH - 1)
    {
        linelen = MOUSE_SPEED_BOX_WIDTH - 1;
    }

    V_DrawHorizLine(box_x + 1, box_y + 4, MOUSE_SPEED_BOX_WIDTH - 2, black);

    if (linelen < redline_x)
    {
        V_DrawHorizLine(box_x + 1, box_y + MOUSE_SPEED_BOX_HEIGHT / 2,
                      linelen, white);
    }
    else
    {
        V_DrawHorizLine(box_x + 1, box_y + MOUSE_SPEED_BOX_HEIGHT / 2,
                        redline_x, white);
        V_DrawHorizLine(box_x + redline_x, box_y + MOUSE_SPEED_BOX_HEIGHT / 2,
                        linelen - redline_x, yellow);
    }


    V_DrawVertLine(box_x + redline_x, box_y + 1,
                 MOUSE_SPEED_BOX_HEIGHT - 2, red);
}

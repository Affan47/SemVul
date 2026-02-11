DrDeathTally(void)
{
    int i, j;
    fixed_t xPos, yPos;
    fixed_t xDelta, yDelta;
    fixed_t xStart, scale;
    int x, y;
    boolean bold;
    static boolean showTotals;
    int temp;

    V_DrawPatch(TALLY_TOP_X, TALLY_TOP_Y,
                W_CacheLumpName("tallytop", PU_CACHE));
    V_DrawPatch(TALLY_LEFT_X, TALLY_LEFT_Y,
                W_CacheLumpName("tallylft", PU_CACHE));
    if (intertime < TALLY_EFFECT_TICKS)
    {
        showTotals = false;
        scale = (intertime * FRACUNIT) / TALLY_EFFECT_TICKS;
        xDelta = FixedMul(scale, TALLY_FINAL_X_DELTA);
        yDelta = FixedMul(scale, TALLY_FINAL_Y_DELTA);
        xStart = TALLY_START_XPOS - FixedMul(scale,
                                             TALLY_START_XPOS -
                                             TALLY_STOP_XPOS);
        yPos =
            TALLY_START_YPOS - FixedMul(scale,
                                        TALLY_START_YPOS - TALLY_STOP_YPOS);
    }
    else
    {
        xDelta = TALLY_FINAL_X_DELTA;
        yDelta = TALLY_FINAL_Y_DELTA;
        xStart = TALLY_STOP_XPOS;
        yPos = TALLY_STOP_YPOS;
    }
    if (intertime >= TALLY_EFFECT_TICKS && showTotals == false)
    {
        showTotals = true;
        S_StartSound(NULL, SFX_PLATFORM_STOP);
    }
    y = yPos >> FRACBITS;
    for (i = 0; i < MAXPLAYERS; i++)
    {
        xPos = xStart;
        for (j = 0; j < MAXPLAYERS; j++, xPos += xDelta)
        {
            x = xPos >> FRACBITS;
            bold = (i == consoleplayer || j == consoleplayer);
            if (playeringame[i] && playeringame[j])
            {
                if (bold)
                {
                    DrNumberBold(players[i].frags[j], x, y, 100);
                }
                else
                {
                    DrNumber(players[i].frags[j], x, y, 100);
                }
            }
            else
            {
                temp = MN_TextAWidth("--") / 2;
                if (bold)
                {
                    MN_DrTextAYellow("--", x - temp, y);
                }
                else
                {
                    MN_DrTextA("--", x - temp, y);
                }
            }
        }
        if (showTotals && playeringame[i]
            && !((slaughterboy & (1 << i)) && !(intertime & 16)))
        {
            DrNumber(totalFrags[i], TALLY_TOTALS_X, y, 1000);
        }
        yPos += yDelta;
        y = yPos >> FRACBITS;
    }
}

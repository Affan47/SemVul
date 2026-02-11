credit_alphashow( int alpha )
{
    if (credit_status == 3) return;
    font->align = STK_FONT_ALIGN_LEFT | STK_FONT_ALIGN_TOP;
    stk_font_write(font, stk_display, credit_x + 2, credit_y + 2,
         (int)alpha, credit_str );
    font->align = STK_FONT_ALIGN_CENTER_X | STK_FONT_ALIGN_CENTER_Y;
}

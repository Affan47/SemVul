b_canceldraft(void)
{
    if (b_bottom==b_screenb)
    {
        tbuf+=sprintf(tbuf,"\0338\033[0m\033[2K");
        while (b_current>b_last)
        {
            b_current--;
            tbuf+=sprintf(tbuf,"\033[A\033[2K");
        };
        tbuf+=sprintf(tbuf,"\r"COLORCODE(o_lastcolor));
        tbuf+=sprintf(tbuf,"\0337");
    }
    else
        b_current=b_last;
    o_oldcolor=o_color=o_lastcolor;
    o_prevcolor=o_lastprevcolor;
    o_len=setcolor(out_line,o_lastcolor);
    o_pos=0;
}

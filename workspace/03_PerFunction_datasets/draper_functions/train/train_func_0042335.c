draw_dnline( float x      FL_UNUSED_ARG,
             float y      FL_UNUSED_ARG,
             float w,
             float h,
             int   angle  FL_UNUSED_ARG,
             long  col    FL_UNUSED_ARG )
{
    float t = 0.20;
    float len;

    ps_output("%.3f %.3f LW ", 3.5 / (w + h), 3.5 / (w + h));
    if ((w + h) > 200)
        len = 0.99;
    else if ((w + h) > 150)
        len = 0.98;
    else
        len = 0.93;

    ps_color(FL_RIGHT_BCOL);
    ps_output("-%.3f %.2f M %.3f %.2f LT S\n", len, t, len, t);
    ps_color(FL_LEFT_BCOL);
    ps_output("-%.3f -%.2f M %.3f -%.2f LT S\n", len, t, len, t);
}

p3d_moved(GtkWidget *widget, GdkEventMotion *event,
                 ExtractControls *controls)
{
    gdouble diffx, diffy;

    if (((event->state & GDK_BUTTON1_MASK) == GDK_BUTTON1_MASK))
    {
        controls->rm[0][0] = controls->rm[1][1] = controls->rm[2][2] = 1;
        controls->rm[1][0] = controls->rm[2][0] = controls->rm[0][1] = controls->rm[0][2] = 0;
        controls->rm[1][2] = controls->rm[2][1] = 0;

        diffx = event->x - controls->rpx;
        diffy = event->y - controls->rpy;
        controls->rpx = event->x;
        controls->rpy = event->y;

        rotate(controls, -0.02*diffy, 0.02*diffx, 0);


        gtk_widget_queue_draw(widget);
    }

    return TRUE;
}

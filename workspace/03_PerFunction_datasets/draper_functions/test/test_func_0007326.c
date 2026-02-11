gdk_pixbuf_animation_get_iter (GdkPixbufAnimation *animation,
                               const GTimeVal     *start_time)
{
        GTimeVal val;

        g_return_val_if_fail (GDK_IS_PIXBUF_ANIMATION (animation), NULL);


        if (start_time)
                val = *start_time;
        else
                g_get_current_time (&val);

        return GDK_PIXBUF_ANIMATION_GET_CLASS (animation)->get_iter (animation, &val);
}

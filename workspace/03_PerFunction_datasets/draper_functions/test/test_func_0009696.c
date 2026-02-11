on_image_effect_activate               (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
    gpaint_canvas *canvas = canvas_lookup(GTK_WIDGET(menuitem));
    const gchar *name = gtk_widget_get_name(GTK_WIDGET(menuitem));
    gpaint_drawing *drawing = canvas->drawing;
    gpaint_image *input;
    gpaint_image *output;
    ImageEffect effect;

    effect = image_lookup_effect(name);
    g_assert(effect);

    input  = drawing_create_image(drawing);
    output = image_new(drawing->width, drawing->height);

    (*effect)(input, output);

    image_draw_on_pixmap(output, &drawing->backing_pixmap, drawing->gc);
    drawing_modified(drawing);
    image_free(input);
    image_free(output);

    canvas_redraw(canvas);
}

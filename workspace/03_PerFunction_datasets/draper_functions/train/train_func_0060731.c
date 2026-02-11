set_text_path (glLabelText      *this,
               cairo_t          *cr,
               gboolean          screen_flag,
               glMergeRecord    *record)
{
        gdouble               object_w, object_h;
        gdouble               raw_w, raw_h;
        gchar                *text;
        GList                *lines;
        gdouble               font_size;
        gboolean              auto_shrink;
        PangoLayout          *layout;
        PangoStyle            style;
        PangoFontDescription *desc;
        cairo_font_options_t *font_options;
        PangoContext         *context;


        gl_debug (DEBUG_LABEL, "START");

        cairo_save (cr);

        gl_label_object_get_size (GL_LABEL_OBJECT (this), &object_w, &object_h);
        gl_label_object_get_raw_size (GL_LABEL_OBJECT (this), &raw_w, &raw_h);

        lines = gl_label_text_get_lines (this);
        text = gl_text_node_lines_expand (lines, record);

        style = this->priv->font_italic_flag ? PANGO_STYLE_ITALIC : PANGO_STYLE_NORMAL;

        font_size   = this->priv->font_size * FONT_SCALE;
        auto_shrink = gl_label_text_get_auto_shrink (this);
        if (!screen_flag && record && auto_shrink && (raw_w != 0.0))
        {
                font_size = auto_shrink_font_size (cr,
                                                   this->priv->font_family,
                                                   font_size,
                                                   this->priv->font_weight,
                                                   style,
                                                   text,
                                                   object_w);
        }


        layout = pango_cairo_create_layout (cr);

        font_options = cairo_font_options_create ();
        cairo_font_options_set_hint_style (font_options, CAIRO_HINT_STYLE_NONE);
        cairo_font_options_set_hint_metrics (font_options, CAIRO_HINT_METRICS_OFF);
        context = pango_layout_get_context (layout);
        pango_cairo_context_set_font_options (context, font_options);
        cairo_font_options_destroy (font_options);

        desc = pango_font_description_new ();
        pango_font_description_set_family (desc, this->priv->font_family);
        pango_font_description_set_weight (desc, this->priv->font_weight);
        pango_font_description_set_size   (desc, font_size * PANGO_SCALE);
        pango_font_description_set_style  (desc, style);
        pango_layout_set_font_description (layout, desc);
        pango_font_description_free       (desc);

        pango_layout_set_text (layout, text, -1);
        pango_layout_set_spacing (layout, font_size * (this->priv->line_spacing-1) * PANGO_SCALE);
        if (raw_w == 0.0)
        {
                pango_layout_set_width (layout, -1);
        }
        else
        {
                pango_layout_set_width (layout, object_w * PANGO_SCALE);
        }
        pango_layout_set_wrap (layout, PANGO_WRAP_WORD);
        pango_layout_set_alignment (layout, this->priv->align);


        cairo_move_to (cr, GL_LABEL_TEXT_MARGIN, 0);
        pango_cairo_layout_path (cr, layout);

        g_object_unref (layout);
        gl_text_node_lines_free (&lines);

        cairo_restore (cr);

        gl_debug (DEBUG_LABEL, "END");
}

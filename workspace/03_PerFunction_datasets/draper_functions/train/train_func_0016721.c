copy (glLabelObject *dst_object,
      glLabelObject *src_object)
{
        glLabelImage     *src_limage = (glLabelImage *)src_object;
        glLabelImage     *new_limage = (glLabelImage *)dst_object;
        glTextNode       *filename;
        GdkPixbuf        *pixbuf;
        gchar            *contents;
        glLabel          *src_label, *dst_label;
        GHashTable       *cache;

        gl_debug (DEBUG_LABEL, "START");

        g_return_if_fail (src_limage && GL_IS_LABEL_IMAGE (src_limage));
        g_return_if_fail (new_limage && GL_IS_LABEL_IMAGE (new_limage));

        filename = gl_label_image_get_filename (src_limage);


        if ( !filename->field_flag && (src_limage->priv->type != FILE_TYPE_NONE) )
        {
                src_label = gl_label_object_get_parent (src_object);
                dst_label = gl_label_object_get_parent (dst_object);

                switch ( src_limage->priv->type )
                {

                case FILE_TYPE_PIXBUF:
                        pixbuf = src_limage->priv->pixbuf;
                        if ( pixbuf != NULL ) {
                                cache = gl_label_get_pixbuf_cache (dst_label);
                                gl_pixbuf_cache_add_pixbuf (cache, filename->data, pixbuf);
                        }
                        break;

                case FILE_TYPE_SVG:
                        cache = gl_label_get_svg_cache (src_label);
                        contents = gl_svg_cache_get_contents (cache, filename->data);
                        if ( contents != NULL ) {
                                cache = gl_label_get_svg_cache (dst_label);
                                gl_svg_cache_add_svg (cache, filename->data, contents);
                                g_free (contents);
                        }
                        break;

                default:
                        break;

                }
        }

        gl_label_image_set_filename (new_limage, filename, FALSE);
        gl_text_node_free (&filename);

        gl_debug (DEBUG_LABEL, "END");
}

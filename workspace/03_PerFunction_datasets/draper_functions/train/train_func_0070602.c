gl_label_image_finalize (GObject *object)
{
        glLabelObject *lobject = GL_LABEL_OBJECT (object);
        glLabelImage  *this  = GL_LABEL_IMAGE (object);
        glLabel       *label;
        GHashTable    *cache;

        g_return_if_fail (object && GL_IS_LABEL_IMAGE (object));

        if (!this->priv->filename->field_flag) {

                label = gl_label_object_get_parent (lobject);

                switch ( this->priv->type )
                {

                case FILE_TYPE_PIXBUF:
                        cache = gl_label_get_pixbuf_cache (label);
                        gl_pixbuf_cache_remove_pixbuf (cache, this->priv->filename->data);
                        break;

                case FILE_TYPE_SVG:
                        cache = gl_label_get_svg_cache (label);
                        gl_svg_cache_remove_svg (cache, this->priv->filename->data);
                        break;

                default:
                        break;

                }

        }
        gl_text_node_free (&this->priv->filename);
        g_free (this->priv);

        G_OBJECT_CLASS (gl_label_image_parent_class)->finalize (object);
}

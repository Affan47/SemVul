button_release ( GdkEventButton *event )
{
	GdkPixbuf *pixbuf;
	gint width, height;

	if ( event->type == GDK_BUTTON_RELEASE )
	{
		if( m_priv->button == event->button )
		{
			if( m_priv->is_draw )
			{
				pixbuf = cv_get_pixbuf ( );
				if(GDK_IS_PIXBUF ( pixbuf ) )
				{
					if(!gdk_pixbuf_get_has_alpha ( pixbuf ) )
					{
						GdkPixbuf *tmp ;
						tmp = gdk_pixbuf_add_alpha(pixbuf, FALSE, 0, 0, 0);
						g_object_unref(pixbuf);
						pixbuf = tmp;
					}

					gdk_drawable_get_size(GDK_DRAWABLE( m_priv->cv->pixmap ),
                                                         &width,
                                                         &height);

					m_priv->pixmap = gdk_pixmap_new(GDK_DRAWABLE( m_priv->cv->pixmap ),
                                                         width,
                                                         height,
                                                         -1);
					gdk_draw_pixbuf(m_priv->pixmap, m_priv->gc, pixbuf, 0, 0, 0, 0,
                                    -1, -1, GDK_RGB_DITHER_NONE, 0, 0);

					m_priv->rect = fill_draw( GDK_DRAWABLE( m_priv->cv->pixmap ),
				    	      m_priv->gc,
				    	      m_priv->fill_color,
				    	      m_priv->x0,
			    		      m_priv->y0);

					g_object_unref(pixbuf);

					save_undo ();
					g_object_unref(m_priv->pixmap);

					file_set_unsave ();
				}
			}
			gtk_widget_queue_draw ( m_priv->cv->widget );
			m_priv->is_draw = FALSE;
		}
	}
	return TRUE;
}

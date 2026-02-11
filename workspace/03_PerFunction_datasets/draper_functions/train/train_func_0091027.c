draw_frame()
{
    if( ! m_draw_frame ) return;

    const int width_win = m_view.get_width();
    const int height_win = m_view.get_height();

    if( m_scroll_window ){


        Gdk::Rectangle rect_frame( 0, 0, width_win, WIDTH_FRAME * 2 );
        m_gc->set_clip_rectangle( rect_frame );
        m_back_frame->draw_drawable( m_gc, m_window, 0, 0, 0, 0, width_win, WIDTH_FRAME );
        m_back_frame->draw_drawable( m_gc, m_window, 0, height_win - WIDTH_FRAME, 0, WIDTH_FRAME, width_win, WIDTH_FRAME );
        m_ready_back_frame = true;
    }

    Gdk::Rectangle rect_clip( 0, 0, width_win, height_win );
    m_gc->set_clip_rectangle( rect_clip );

    m_gc->set_foreground( m_color[ COLOR_FRAME ] );
    m_window->draw_rectangle( m_gc, false, WIDTH_FRAME-1, WIDTH_FRAME-1, width_win-WIDTH_FRAME, height_win-WIDTH_FRAME );
}

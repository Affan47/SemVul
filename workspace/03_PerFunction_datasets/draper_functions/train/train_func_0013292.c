lgl_template_frame_free (lglTemplateFrame *frame)
{
        GList                *p;
        lglTemplateLayout    *layout;
        lglTemplateMarkup    *markup;

        if ( frame != NULL )
        {

                g_free (frame->all.id);
                frame->all.id = NULL;

                for ( p=frame->all.layouts; p != NULL; p=p->next )
                {
                        layout = (lglTemplateLayout *)p->data;

                        lgl_template_layout_free (layout);
                        p->data = NULL;
                }
                g_list_free (frame->all.layouts);
                frame->all.layouts = NULL;

                for ( p=frame->all.markups; p != NULL; p=p->next )
                {
                        markup = (lglTemplateMarkup *)p->data;

                        lgl_template_markup_free (markup);
                        p->data = NULL;
                }
                g_list_free (frame->all.markups);
                frame->all.markups = NULL;

                g_free (frame);

        }

}

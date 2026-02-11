create_new_text(w)
HyperWidget   w;
{
    text_segment *s = w->hyper.first_seg;

    w->hyper.first_seg = w->hyper.last_selected = w->hyper.last_cursor = NULL;

    while(s)
    {
        add_to_text(w,s->text,s->type);
        s = s->next;
    }
    free_text(s);
    calc_new_size(w);
}

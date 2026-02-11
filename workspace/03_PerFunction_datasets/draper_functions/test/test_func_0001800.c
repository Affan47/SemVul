add_window(Window w) {
    client *c,*t;

    if(!(c = (client *)calloc(1,sizeof(client))))
        die("Error calloc!");

    if(head == NULL) {
        c->next = NULL;
        c->prev = NULL;
        c->win = w;
        head = c;
    }
    else {
        for(t=head;t->next;t=t->next);

        c->next = NULL;
        c->prev = t;
        c->win = w;

        t->next = c;
    }

    current = c;
}

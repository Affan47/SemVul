tag_client(struct tag *t, struct client *c)
{

     if(c->tag && !(c->flags & CLIENT_RULED))
     {
          if(c->tag == t)
               return;

          if(!(c->flags & (CLIENT_IGNORE_LAYOUT | CLIENT_FREE)))
               layout_split_arrange_closed(c);

          if(!(c->flags & CLIENT_REMOVEALL))
          {
               SLIST_REMOVE(&c->tag->clients, c, client, tnext);

               if(c->tag->sel == c || W->client == c)
                    client_focus( client_tab_next( client_next(c)));
          }
     }

     c->flags &= ~CLIENT_RULED;

     infobar_elem_screen_update(c->screen, ElemTag);


     if(!t)
          return;

     c->prevtag = c->tag;
     c->tag = t;
     c->screen = t->screen;

     client_update_props(c, CPROP_LOC);

     SLIST_INSERT_HEAD(&t->clients, c, tnext);

     if(c->flags & CLIENT_TABMASTER && c->prevtag)
     {
          struct client *cc;

          SLIST_FOREACH(cc, &c->prevtag->clients, tnext)
               if(cc->tabmaster == c)
               {
                    cc->flags |= CLIENT_IGNORE_LAYOUT;
                    tag_client(t, cc);
               }
     }

     layout_client(c);

     if(t != c->screen->seltag || c->flags & CLIENT_TABBED)
          client_unmap(c);
}

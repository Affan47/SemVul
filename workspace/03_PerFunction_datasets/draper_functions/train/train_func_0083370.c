config_tag(void)
{
     struct screen *s;
     struct tag *t;
     size_t i, n;
     struct conf_sec *sec, **ks, **mb;
     char *name, *tmp;
     int screenid;


     sec = fetch_section_first(NULL, "tags");
     ks = fetch_section(sec, "tag");
     n = fetch_section_count(ks);


     if((mb = fetch_section(sec, "mouse")))
     {
          config_mouse_section(&W->tmp_head.tag, mb);
          free(mb);
     }


     for(i = 0; i < n; ++i)
     {
          name = fetch_opt_first(ks[i], "tag", "name").str;
          screenid = fetch_opt_first(ks[i], "-1", "screen").num;

          SLIST_FOREACH(s, &W->h.screen, next)
               if(screenid == s->id || screenid == -1)
               {
                    t = tag_new(s, name);

                    t->statusctx = status_new_ctx(NULL, NULL);
                    ISTRDUP(t->statusctx.status, fetch_opt_first(ks[i], "", "statusline").str);
                    if(t->statusctx.status)
                         status_parse(&t->statusctx);
               }
     }


     SLIST_FOREACH(s, &W->h.screen, next)
          if(TAILQ_EMPTY(&s->tags))
               tag_new(s, "tag");

     free(ks);
}

uicb_tag_set_with_name(Uicb cmd)
{
     struct tag *t;

     TAILQ_FOREACH(t, &W->screen->tags, next)
          if(!strcmp(cmd, t->name))
          {
               tag_screen(W->screen, t);
               return;
          }
}

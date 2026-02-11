fetch_section_first(struct conf_sec *s, char *name)
{
     struct conf_sec *sec, *ret = NULL;
     TAILQ_HEAD(cshead, conf_sec) *head =
          (s
           ? (struct cshead*)&s->sub
           : (struct cshead*)&config);

     if(!name)
          return NULL;

     TAILQ_FOREACH(sec, head, entry)
          if(sec->name && !strcmp(sec->name, name))
          {
               ret = sec;
               break;
          }

     return ret;
}

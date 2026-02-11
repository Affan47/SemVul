delete_keygrab(struct module *m, int id)
{
  struct mcmd_keygrab *kg=keygrabs, *last=NULL;
  Client *c;

  while(kg) {
    if(kg->owner==m && (id<0 || kg->id==id)) {
      if(last)
	last->next=kg->next;
      else
	keygrabs=kg->next;
      if(!find_keygrab(kg->keycode, kg->modifiers))
	for(c=clients; c; c=c->next)
	  if(c->parent && c->parent!=c->scr->root)
	    XUngrabKey(dpy, kg->keycode, kg->modifiers, c->window);
    } else last=kg;
    kg=kg->next;
  }
}

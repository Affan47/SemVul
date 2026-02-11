AddObject(li, hot, obj)
HTMLInfo li;
HTMLObjectType hot;
void *obj;
{
  HTMLEnv env;
  HTMLObject ho;

  ho = (HTMLObject)MPGet(li->mp, sizeof(struct HTMLObjectP));
  ho->type = hot;
  if (hot == HTML_ENV) ho->o.env = (HTMLEnv)obj;
  else if (hot == HTML_ELEMENT) ho->o.p = (MLElement)obj;
  else if (hot == HTML_TAG) ho->o.p = (MLElement)obj;
  else if (hot == HTML_BEGINTAG) ho->o.p = (MLElement)obj;
  else if (hot == HTML_ENDTAG) ho->o.p = (MLElement)obj;
  else abort();

  if (li->printTags) PrintObject(ho);

  if (hot != HTML_BEGINTAG && hot != HTML_ENDTAG)
  {
    for (env = (HTMLEnv)GListGetHead(li->envstack); env != NULL;
	 env = (HTMLEnv)GListGetNext(li->envstack))
    {
      if (env->tag->m == NULL || (env->tag->m)(li, ho)) break;
    }
    if (env == NULL) return;
  }
  else env = (HTMLEnv)GListGetHead(li->envstack);

  if (hot == HTML_ENV) ho->o.env->penv = env;


  GListAddTail(env->olist, ho);
  GListAddTail(env->slist, ho);

  return;
}

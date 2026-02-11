HTMLDivBegin(li, env, p)
HTMLInfo li;
HTMLEnv env;
MLElement p;
{
  HTMLAttribID aid;

  aid = HTMLAttributeToID(p, "align");
  if (aid == ATTRIB_CENTER) env->ff = FLOW_CENTER_JUSTIFY;
  else if (aid == ATTRIB_LEFT) env->ff = FLOW_LEFT_JUSTIFY;
  else if (aid == ATTRIB_RIGHT) env->ff = FLOW_RIGHT_JUSTIFY;

  HTMLAddLineBreak(li, env);

  return;
}

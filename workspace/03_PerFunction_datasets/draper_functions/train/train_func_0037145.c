get_num_orb(gchar *nameorb)
{
  gchar *orb = g_strdup(nameorb);
  gint k=-1;
  g_strup(orb);
  if(strcmp(orb,"ECP")==0)
	return -1;
  switch(orb[0])
  {
  case 'S' : k=0;break;
  case 'P' : k=1;break;
  case 'D' : k=2;break;
  default : if(orb[0]<='I')
	     k=(gint)orb[0]-(gint)'F'+3;
  }

  g_free(orb);
  return k;
}

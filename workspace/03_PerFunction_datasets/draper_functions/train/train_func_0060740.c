parseAMF(AMFObject *obj, AVal *av, int *depth)
{
  AMFObjectProperty prop = {{0,0}};
  int i;
  char *p, *arg = av->av_val;

  if (arg[1] == ':')
    {
      p = (char *)arg+2;
      switch(arg[0])
	{
	case 'B':
	  prop.p_type = AMF_BOOLEAN;
	  prop.p_vu.p_number = atoi(p);
	  break;
	case 'S':
	  prop.p_type = AMF_STRING;
	  prop.p_vu.p_aval.av_val = p;
	  prop.p_vu.p_aval.av_len = av->av_len - (p-arg);
	  break;
	case 'N':
	  prop.p_type = AMF_NUMBER;
	  prop.p_vu.p_number = strtod(p, NULL);
	  break;
	case 'Z':
	  prop.p_type = AMF_NULL;
	  break;
	case 'O':
	  i = atoi(p);
	  if (i)
	    {
	      prop.p_type = AMF_OBJECT;
	    }
	  else
	    {
	      (*depth)--;
	      return 0;
	    }
	  break;
	default:
	  return -1;
	}
    }
  else if (arg[2] == ':' && arg[0] == 'N')
    {
      p = strchr(arg+3, ':');
      if (!p || !*depth)
	return -1;
      prop.p_name.av_val = (char *)arg+3;
      prop.p_name.av_len = p - (arg+3);

      p++;
      switch(arg[1])
	{
	case 'B':
	  prop.p_type = AMF_BOOLEAN;
	  prop.p_vu.p_number = atoi(p);
	  break;
	case 'S':
	  prop.p_type = AMF_STRING;
	  prop.p_vu.p_aval.av_val = p;
	  prop.p_vu.p_aval.av_len = av->av_len - (p-arg);
	  break;
	case 'N':
	  prop.p_type = AMF_NUMBER;
	  prop.p_vu.p_number = strtod(p, NULL);
	  break;
	case 'O':
	  prop.p_type = AMF_OBJECT;
	  break;
	default:
	  return -1;
	}
    }
  else
    return -1;

  if (*depth)
    {
      AMFObject *o2;
      for (i=0; i<*depth; i++)
	{
	  o2 = &obj->o_props[obj->o_num-1].p_vu.p_object;
	  obj = o2;
	}
    }
  AMF_AddProp(obj, &prop);
  if (prop.p_type == AMF_OBJECT)
    (*depth)++;
  return 0;
}

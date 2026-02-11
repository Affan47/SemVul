dumpAMF(AMFObject *obj, char *ptr, AVal *argv, int *argc)
{
  int i, ac = *argc;
  const char opt[] = "NBSO Z";

  for (i = 0; i < obj->o_num; i++)
    {
      AMFObjectProperty *p = &obj->o_props[i];
      if ((p->p_type == AMF_ECMA_ARRAY) || (p->p_type == AMF_STRICT_ARRAY))
        p->p_type = AMF_OBJECT;
      argv[ac].av_val = ptr+1;
      argv[ac++].av_len = 2;
      ptr += sprintf(ptr, " -C ");
      argv[ac].av_val = ptr;
      if (p->p_name.av_val)
	*ptr++ = 'N';
      *ptr++ = opt[p->p_type];
      *ptr++ = ':';
      if (p->p_name.av_val)
	ptr += sprintf(ptr, "%.*s:", p->p_name.av_len, p->p_name.av_val);
      switch(p->p_type)
	{
	case AMF_BOOLEAN:
	  *ptr++ = p->p_vu.p_number != 0 ? '1' : '0';
	  argv[ac].av_len = ptr - argv[ac].av_val;
	  break;
	case AMF_STRING:
	  memcpy(ptr, p->p_vu.p_aval.av_val, p->p_vu.p_aval.av_len);
	  ptr += p->p_vu.p_aval.av_len;
	  argv[ac].av_len = ptr - argv[ac].av_val;
	  break;
	case AMF_NUMBER:
	  ptr += sprintf(ptr, "%f", p->p_vu.p_number);
	  argv[ac].av_len = ptr - argv[ac].av_val;
	  break;
	case AMF_OBJECT:
	  *ptr++ = '1';
	  argv[ac].av_len = ptr - argv[ac].av_val;
	  ac++;
	  *argc = ac;
	  ptr = dumpAMF(&p->p_vu.p_object, ptr, argv, argc);
	  ac = *argc;
	  argv[ac].av_val = ptr+1;
	  argv[ac++].av_len = 2;
	  argv[ac].av_val = ptr+4;
	  argv[ac].av_len = 3;
	  ptr += sprintf(ptr, " -C O:0");
	  break;
	case AMF_NULL:
	default:
	  argv[ac].av_len = ptr - argv[ac].av_val;
	  break;
	}
      ac++;
    }
  *argc = ac;
  return ptr;
}

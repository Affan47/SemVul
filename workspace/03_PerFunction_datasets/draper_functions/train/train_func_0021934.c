NewError(const xstring& t0,int code,const char *msg)
{
   xmap_p<BeNode> m;
   m.add("t",new BeNode(t0));
   m.add("y",new BeNode("e",1));
   xarray_p<BeNode> e;
   e.append(new BeNode(code));
   e.append(new BeNode(msg));
   m.add("e",new BeNode(&e));
   return new BeNode(&m);
}

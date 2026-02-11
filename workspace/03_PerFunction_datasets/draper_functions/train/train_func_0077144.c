get_skel_small_Plugin(POA_Plugin *servant,
const char *opname,gpointer *m_data, gpointer *impl)
{
switch(opname[0]) {
case 'd':
if(strcmp((opname + 1), "oPluginTest")) break;
*impl = (gpointer)servant->vepv->Plugin_epv->doPluginTest;
{ORBit_IInterface *volatile _t_=&Plugin__iinterface;*m_data = (gpointer)&_t_->methods._buffer [0];}
return (ORBitSmallSkeleton)_ORBIT_skel_small_Plugin_doPluginTest;
break;
default: break;
}
return NULL;
}

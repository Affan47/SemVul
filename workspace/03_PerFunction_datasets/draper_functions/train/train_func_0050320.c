get_skel_small_Bonobo_GenericFactory(POA_Bonobo_GenericFactory *servant,
const char *opname,gpointer *m_data, gpointer *impl)
{
switch(opname[0]) {
case 'c':
if(strcmp((opname + 1), "reateObject")) break;
*impl = (gpointer)servant->vepv->Bonobo_GenericFactory_epv->createObject;
{ORBit_IInterface *volatile _t_=&Bonobo_GenericFactory__iinterface;*m_data = (gpointer)&_t_->methods._buffer [0];}
return (ORBitSmallSkeleton)_ORBIT_skel_small_Bonobo_GenericFactory_createObject;
break;
case 'q':
if(strcmp((opname + 1), "ueryInterface")) break;
*impl = (gpointer)servant->vepv->Bonobo_Unknown_epv->queryInterface;
{ORBit_IInterface *volatile _t_=&Bonobo_Unknown__iinterface;*m_data = (gpointer)&_t_->methods._buffer [2];}
return (ORBitSmallSkeleton)_ORBIT_skel_small_Bonobo_Unknown_queryInterface;
break;
case 'r':
if(strcmp((opname + 1), "ef")) break;
*impl = (gpointer)servant->vepv->Bonobo_Unknown_epv->ref;
{ORBit_IInterface *volatile _t_=&Bonobo_Unknown__iinterface;*m_data = (gpointer)&_t_->methods._buffer [0];}
return (ORBitSmallSkeleton)_ORBIT_skel_small_Bonobo_Unknown_ref;
break;
case 'u':
if(strcmp((opname + 1), "nref")) break;
*impl = (gpointer)servant->vepv->Bonobo_Unknown_epv->unref;
{ORBit_IInterface *volatile _t_=&Bonobo_Unknown__iinterface;*m_data = (gpointer)&_t_->methods._buffer [1];}
return (ORBitSmallSkeleton)_ORBIT_skel_small_Bonobo_Unknown_unref;
break;
default: break;
}
return NULL;
}

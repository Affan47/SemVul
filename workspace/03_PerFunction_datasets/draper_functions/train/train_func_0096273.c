node_FreeValue(unsigned char type,unsigned long long value)
{
  switch(type)
  {
    case NODE_TYPE_NULL:
         break;
    case NODE_TYPE_INT:
    case NODE_TYPE_FLOAT:
    case NODE_TYPE_DOUBLE:
    case NODE_TYPE_UINT8:
    case NODE_TYPE_SINT8:
    case NODE_TYPE_BOOL:
    case NODE_TYPE_UINT16:
    case NODE_TYPE_SINT16:
    case NODE_TYPE_UINT32:
    case NODE_TYPE_SINT32:
    case NODE_TYPE_SINT64:
    case NODE_TYPE_UINT64:


         break;
    case NODE_TYPE_STRING:
         if(((char*)(unsigned long)value)!=NULL)
           free((char*)(unsigned long)value);
         break;
    case NODE_TYPE_ARRAY:
         if(((node_array*)(unsigned long)value)!=NULL)
           node_FreeArray((node_array*)(unsigned long)value,True);
         break;
    case NODE_TYPE_NODE:


         break;
    case NODE_TYPE_STUB:
         break;
    case NODE_TYPE_USER:
         break;
    case NODE_TYPE_BINARY:
         if(((node_binary*)(unsigned long)value)!=NULL)
           node_FreeBinary((node_binary*)(unsigned long)value,True);
         break;
    default:
         break;
  }
}

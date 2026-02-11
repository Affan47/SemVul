node_CopyValue(node *n)
{
  unsigned long long r = 0;
  switch(n->type)
  {
    case NODE_TYPE_FLOAT:
    case NODE_TYPE_DOUBLE:


    printf("copying double:%f\n",node_GetDouble(n));
    double *d = (double*)&r;
    *d = node_GetDouble(n);
    printf("copying double2:%f\n",*d);
    break;
    case NODE_TYPE_NULL:
    case NODE_TYPE_INT:
    case NODE_TYPE_UINT8:
    case NODE_TYPE_SINT8:
    case NODE_TYPE_BOOL:
    case NODE_TYPE_UINT16:
    case NODE_TYPE_SINT16:
    case NODE_TYPE_UINT32:
    case NODE_TYPE_SINT32:
    case NODE_TYPE_SINT64:
    case NODE_TYPE_UINT64:
    case NODE_TYPE_NODE:
    case NODE_TYPE_USER:
         r = n->value;
         break;
    case NODE_TYPE_STRING:
         {
            char *tmp = str_Copy((char*)(unsigned long)n->value);
            r = (unsigned long long)(unsigned long)tmp;


         }
         break;
    case NODE_TYPE_ARRAY:
         {
            node_array *tmp = node_CopyArray((node_array*)(unsigned long)n->value,True);
            r = (unsigned long long)(unsigned long)tmp;
         }
         break;
    case NODE_TYPE_BINARY:
         {

            node_binary *tmp = node_CopyBinary(((node_binary*)(unsigned long)n->value)->value,((node_binary*)(unsigned long)n->value)->len);
            r = (unsigned long long)(unsigned long)tmp;
         }
         break;
    default:
         break;
  }
  return(r);
}

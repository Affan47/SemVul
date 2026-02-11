_g_ir_node_new (GIrNodeTypeId  type,
	       GIrModule     *module)
{
  GIrNode *node = NULL;

  switch (type)
    {
   case G_IR_NODE_FUNCTION:
   case G_IR_NODE_CALLBACK:
      node = g_malloc0 (sizeof (GIrNodeFunction));
      break;

   case G_IR_NODE_PARAM:
      node = g_malloc0 (sizeof (GIrNodeParam));
      break;

   case G_IR_NODE_TYPE:
      node = g_malloc0 (sizeof (GIrNodeType));
      break;

    case G_IR_NODE_OBJECT:
    case G_IR_NODE_INTERFACE:
      node = g_malloc0 (sizeof (GIrNodeInterface));
      break;

    case G_IR_NODE_SIGNAL:
      node = g_malloc0 (sizeof (GIrNodeSignal));
      break;

    case G_IR_NODE_PROPERTY:
      node = g_malloc0 (sizeof (GIrNodeProperty));
      break;

    case G_IR_NODE_VFUNC:
      node = g_malloc0 (sizeof (GIrNodeFunction));
      break;

    case G_IR_NODE_FIELD:
      node = g_malloc0 (sizeof (GIrNodeField));
      break;

    case G_IR_NODE_ENUM:
    case G_IR_NODE_FLAGS:
      node = g_malloc0 (sizeof (GIrNodeEnum));
      break;

    case G_IR_NODE_BOXED:
      node = g_malloc0 (sizeof (GIrNodeBoxed));
      break;

    case G_IR_NODE_STRUCT:
      node = g_malloc0 (sizeof (GIrNodeStruct));
      break;

    case G_IR_NODE_VALUE:
      node = g_malloc0 (sizeof (GIrNodeValue));
      break;

    case G_IR_NODE_CONSTANT:
      node = g_malloc0 (sizeof (GIrNodeConstant));
      break;

    case G_IR_NODE_XREF:
      node = g_malloc0 (sizeof (GIrNodeXRef));
      break;

    case G_IR_NODE_UNION:
      node = g_malloc0 (sizeof (GIrNodeUnion));
      break;

    default:
      g_error ("Unhandled node type %d\n", type);
      break;
    }

  node->type = type;
  node->module = module;
  node->offset = 0;
  node->attributes = g_hash_table_new_full (g_str_hash, g_str_equal,
                                            g_free, g_free);

  return node;
}

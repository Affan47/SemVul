write_header_stmts(FILE *header, const statement_list_t *stmts, const type_t *iface, int ignore_funcs)
{
  const statement_t *stmt;
  if (stmts) LIST_FOR_EACH_ENTRY( stmt, stmts, const statement_t, entry )
  {
    switch (stmt->type)
    {
      case STMT_TYPE:
        if (type_get_type(stmt->u.type) == TYPE_INTERFACE)
        {
          type_t *iface = stmt->u.type;
          if (is_object(iface)) is_object_interface++;
          if (is_attr(stmt->u.type->attrs, ATTR_DISPINTERFACE) || is_object(stmt->u.type))
          {
            write_com_interface_start(header, iface);
            write_header_stmts(header, type_iface_get_stmts(iface), stmt->u.type, TRUE);
            write_com_interface_end(header, iface);
          }
          else
          {
            write_rpc_interface_start(header, iface);
            write_header_stmts(header, type_iface_get_stmts(iface), iface, FALSE);
            write_rpc_interface_end(header, iface);
          }
          if (is_object(iface)) is_object_interface--;
        }
        else if (type_get_type(stmt->u.type) == TYPE_COCLASS)
          write_coclass(header, stmt->u.type);
        else
        {
          write_type_def_or_decl(header, stmt->u.type, FALSE, NULL);
          fprintf(header, ";\n\n");
        }
        break;
      case STMT_TYPEREF:


        if (type_get_type(stmt->u.type) == TYPE_INTERFACE && !stmt->u.type->written)
          write_forward(header, stmt->u.type);
        break;
      case STMT_IMPORTLIB:
      case STMT_MODULE:

        break;
      case STMT_IMPORT:

        break;
      case STMT_TYPEDEF:
      {
        const type_list_t *type_entry = stmt->u.type_list;
        for (; type_entry; type_entry = type_entry->next)
	  write_typedef(header, type_entry->type);
        break;
      }
      case STMT_LIBRARY:
        write_library(header, stmt->u.lib);
        write_header_stmts(header, stmt->u.lib->stmts, NULL, FALSE);
        break;
      case STMT_CPPQUOTE:
        fprintf(header, "%s\n", stmt->u.str);
        break;
      case STMT_DECLARATION:
        if (iface && type_get_type(stmt->u.var->type) == TYPE_FUNCTION)
        {
          if (!ignore_funcs)
          {
            int prefixes_differ = strcmp(prefix_client, prefix_server);

            if (prefixes_differ)
            {
              fprintf(header, "/* client prototype */\n");
              write_function_proto(header, iface, stmt->u.var, prefix_client);
              fprintf(header, "/* server prototype */\n");
            }
            write_function_proto(header, iface, stmt->u.var, prefix_server);
          }
        }
        else
          write_declaration(header, stmt->u.var);
        break;
    }
  }
}

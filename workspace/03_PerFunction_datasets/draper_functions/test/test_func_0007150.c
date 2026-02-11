db_parser_start_element_display (ParserData *data,
                                 const gchar **attribute_name,
                                 const gchar **attribute_value,
                                 GError **error)
{
        sqlite3_stmt *stmt = data->insert_display_stmt;
        gint ii;


        db_parser_bind_text (stmt, "@flipx", "no");

        db_parser_bind_text (stmt, "@game", data->game);

        for (ii = 0; attribute_name[ii] != NULL; ii++)
        {
                const gchar *param;

                if (attribute_name[ii] == intern.type)
                        param = "@type";
                else if (attribute_name[ii] == intern.rotate)
                        param = "@rotate";
                else if (attribute_name[ii] == intern.flipx)
                        param = "@flipx";
                else if (attribute_name[ii] == intern.width)
                        param = "@width";
                else if (attribute_name[ii] == intern.height)
                        param = "@height";
                else if (attribute_name[ii] == intern.refresh)
                        param = "@refresh";
                else if (attribute_name[ii] == intern.pixclock)
                        param = "@pixclock";
                else if (attribute_name[ii] == intern.htotal)
                        param = "@htotal";
                else if (attribute_name[ii] == intern.hbend)
                        param = "@hbend";
                else if (attribute_name[ii] == intern.hbstart)
                        param = "@hbstart";
                else if (attribute_name[ii] == intern.vtotal)
                        param = "@vtotal";
                else if (attribute_name[ii] == intern.vbend)
                        param = "@vbend";
                else if (attribute_name[ii] == intern.vbstart)
                        param = "@vbstart";
                else
                        continue;

                db_parser_bind_text (stmt, param, attribute_value[ii]);
        }
}

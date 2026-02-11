matrix_readdata_to_container(const guchar** fp,
                                          const gchar* name,
                                          const gchar* metaname,
                                          GwyContainer* container,
                                          GwyContainer* metacontainer,
                                          guint32 check)
{
    gchar* id = NULL;
    if(check == 1) {
        guint32 a = gwy_get_guint32_le(fp);
        if(a != 0 ) {
            *fp -= 4;
            gwy_container_set_int32_by_name(container, name, a);
            if(metacontainer != NULL) {
              gchar val[30];
              g_snprintf(val, sizeof(val), "%u", a);
              gwy_container_set_string_by_name(metacontainer, metaname,
                                               (guchar*)g_strdup(val));
            }
            return 0;
        }
    }

    id = g_strndup((gchar*)*fp, 4);
    *fp += 4;
    if(0 == strncmp(id, "GNOL", 4)) {

        guint32 v = gwy_get_guint32_le(fp);
        gwy_container_set_int32_by_name(container, name, v);
        if(metacontainer != NULL) {
          gchar val[30];
          g_snprintf(val, sizeof(val), "%u", v);
          gwy_container_set_string_by_name(metacontainer,
                                           metaname,
                                           (guchar*)g_strdup(val));
        }
        g_free(id);
        return 0;
    } else if(0 == strncmp(id, "LOOB", 4)) {

        guint32 a = gwy_get_guint32_le(fp);
        gwy_container_set_boolean_by_name(container, name, a != 0);
        if(metacontainer != NULL) {
          gchar val[30];
          g_snprintf(val, sizeof(val), "%i", a);
          gwy_container_set_string_by_name(metacontainer,
                                           metaname,
                                           (guchar*)g_strdup(val));
        }
        g_free(id);
        return 0;
    } else if(0 == strncmp(id, "BUOD", 4)) {

        gdouble v = gwy_get_gdouble_le(fp);
        gwy_container_set_double_by_name(container, name, v);
        if(metacontainer != NULL) {
          gchar val[30];
          g_snprintf(val, sizeof(val), "%e", v);
          gwy_container_set_string_by_name(metacontainer,
                                           metaname,
                                           (guchar*)g_strdup(val));
        }
        g_free(id);
        return 0;
    } else if(0 == strncmp(id, "GRTS", 4)) {

        gchar* str;
        str = matrix_readstring(fp, NULL);
        gwy_container_set_string_by_name(container,
                                         name, (guchar*)str);
        if(metacontainer != NULL) {
          gwy_container_set_string_by_name(metacontainer,
                                           metaname,
                                           (guchar*)g_strdup(str));
        }
        g_free(id);
        return 0;
    }
    g_free(id);
    return 1;
}

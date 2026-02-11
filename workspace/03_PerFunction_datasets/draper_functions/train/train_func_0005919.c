write_counts(FILE* out, ...)
{
    va_list ap;
    char *type;
    gboolean success = TRUE;

    va_start(ap, out);
    type = g_strdup (va_arg(ap, char *));

    while (success && type)
    {
        int amount = va_arg(ap, int);

        if (amount != 0)
        {
#if GNUCASH_REALLY_BUILD_AN_XML_TREE_ON_OUTPUT
            char *val;
            xmlNodePtr node;

            val = g_strdup_printf("%d", amount);

            node = xmlNewNode(NULL, BAD_CAST COUNT_DATA_TAG);


            xmlSetProp(node, BAD_CAST "cd:type", checked_char_cast (type));
            xmlNodeAddContent(node, checked_char_cast (val));
            g_free(val);
	    g_free (type);

            xmlElemDump(out, NULL, node);
            xmlFreeNode(node);

            if (ferror(out) || fprintf(out, "\n") < 0)
            {
                success = FALSE;
                break;
            }
#else
            if (fprintf(out, "<%s %s=\"%s\">%d</%s>\n",
                        COUNT_DATA_TAG, "cd:type", type, amount, COUNT_DATA_TAG) < 0)
            {
                success = FALSE;
                break;
            }
#endif

        }

        type = va_arg(ap, char *);
    }

    va_end(ap);
    return success;
}

lgl_db_lookup_template_from_brand_part(const gchar *brand,
                                       const gchar *part)
{
        gchar            *name;
        lglTemplate      *template;
        lglTemplate      *new_template;

        if (!model)
        {
                lgl_db_init ();
        }

        if ((brand == NULL) || (part == NULL))
        {

                return lgl_template_dup ((lglTemplate *) model->templates->data);
        }

        name = g_strdup_printf ("%s %s", brand, part);
        template = g_hash_table_lookup (model->template_cache, name);

        if (template)
        {
                new_template = lgl_template_dup (template);
                return new_template;
        }


        g_free (name);
        return lgl_template_dup ((lglTemplate *) model->templates->data);
}

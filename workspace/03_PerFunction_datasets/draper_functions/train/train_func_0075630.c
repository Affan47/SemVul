lgl_db_print_known_categories (void)
{
        GList       *p;
        lglCategory *category;

        if (!model)
        {
                lgl_db_init ();
        }

        g_print ("%s():\n", __FUNCTION__);
        for (p = model->categories; p != NULL; p = p->next)
        {
                category = (lglCategory *) p->data;

                g_print ("CATEGORY id=\"%s\", name=\"%s\"\n", category->id, category->name);
        }
        g_print ("\n");

}

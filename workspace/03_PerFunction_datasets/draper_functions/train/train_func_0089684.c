free_xkb_component_names (XkbComponentNamesRec *p)
{
        g_return_if_fail (p != NULL);

        free (p->keymap);
        free (p->keycodes);
        free (p->types);
        free (p->compat);
        free (p->symbols);
        free (p->geometry);

        g_free (p);
}

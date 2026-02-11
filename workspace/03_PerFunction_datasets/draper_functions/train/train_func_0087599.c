_key_binding_text_get(E_Config_Binding_Key *bi)
{
   char b[256] = "";

   if (!bi) return NULL;

   if (bi->modifiers & E_BINDING_MODIFIER_CTRL)
     strcat(b, _("CTRL"));

   if (bi->modifiers & E_BINDING_MODIFIER_ALT)
     {
        if (b[0]) strcat(b, " + ");
        strcat(b, _("ALT"));
     }

   if (bi->modifiers & E_BINDING_MODIFIER_SHIFT)
     {
        if (b[0]) strcat(b, " + ");
        strcat(b, _("SHIFT"));
     }

   if (bi->modifiers & E_BINDING_MODIFIER_WIN)
     {
        if (b[0]) strcat(b, " + ");
        strcat(b, _("WIN"));
     }

   if (bi->key && bi->key[0])
     {
        char *l;
        if (b[0]) strcat(b, " + ");

        l = strdup(bi->key);
        l[0] = (char)toupper(bi->key[0]);
        strcat(b, l);
        free(l);
     }


   if (!b[0]) return strdup(TEXT_NONE_ACTION_KEY);
   return strdup(b);
}

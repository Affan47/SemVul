_e_gadcon_client_class_feature_check(const E_Gadcon_Client_Class *cc, const char *name, void *feature)
{
   if (!feature)
     {
        e_util_dialog_show(_("Insufficent gadcon support"),
                           _("Module %s needs to support %s"),
                           cc->name, name);
        return 0;
     }
   return 1;
}

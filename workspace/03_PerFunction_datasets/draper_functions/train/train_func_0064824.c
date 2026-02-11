_fill_data(E_Config_Dialog_Data *cfdata)
{
   Eina_List *l;
   E_Config_Binding_Acpi *binding;

   EINA_LIST_FOREACH(e_config->acpi_bindings, l, binding)
     {
        E_Config_Binding_Acpi *b2;

        b2 = E_NEW(E_Config_Binding_Acpi, 1);
        b2->context = binding->context;
        b2->type = binding->type;
        b2->status = binding->status;
        b2->action = eina_stringshare_ref(binding->action);
        b2->params = eina_stringshare_ref(binding->params);
        cfdata->bindings = eina_list_append(cfdata->bindings, b2);
     }
}

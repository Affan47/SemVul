_create_data(E_Config_Dialog *cfd EINA_UNUSED)
{
   E_Config_Dialog_Data *cfdata;


   if (!(cfdata = E_NEW(E_Config_Dialog_Data, 1)))
     return NULL;

   return cfdata;
}

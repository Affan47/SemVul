_free_data(E_Config_Dialog *cfd, E_Config_Dialog_Data *cfdata)
{
   Instance *inst = cfd->data;

   inst->cfd = NULL;

   E_FREE(cfdata);
}

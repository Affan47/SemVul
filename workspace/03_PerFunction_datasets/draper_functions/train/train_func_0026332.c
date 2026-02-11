e_intl_input_method_config_read(Eet_File *imc_file)
{
   E_Input_Method_Config *imc;

   imc = NULL;
   if (imc_file)
     {
	imc = (E_Input_Method_Config *) eet_data_read(imc_file, _e_intl_input_method_config_edd, "imc");
     }
   return imc;
}

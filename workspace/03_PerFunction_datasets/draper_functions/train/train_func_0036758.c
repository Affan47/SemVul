Initialise(void)
{
  if (OpenLibrary())
  {

    ADL_Main_Control_Create          = (ADL_MAIN_CONTROL_CREATE)          dlsym(m_handle, "ADL_Main_Control_Create");
	  ADL_Main_Control_Destroy         = (ADL_MAIN_CONTROL_DESTROY)         dlsym(m_handle, "ADL_Main_Control_Destroy");
	  ADL_Adapter_NumberOfAdapters_Get = (ADL_ADAPTER_NUMBEROFADAPTERS_GET) dlsym(m_handle, "ADL_Adapter_NumberOfAdapters_Get");
	  ADL_Adapter_AdapterInfo_Get      = (ADL_ADAPTER_ADAPTERINFO_GET)      dlsym(m_handle, "ADL_Adapter_AdapterInfo_Get");
	  ADL_Display_DisplayInfo_Get      = (ADL_DISPLAY_DISPLAYINFO_GET)      dlsym(m_handle, "ADL_Display_DisplayInfo_Get");
	  ADL_Display_EdidData_Get         = (ADL_DISPLAY_EDIDDATA_GET)         dlsym(m_handle, "ADL_Display_EdidData_Get");


    if (ADL_Main_Control_Create &&
        ADL_Main_Control_Destroy &&
        ADL_Adapter_NumberOfAdapters_Get &&
        ADL_Adapter_AdapterInfo_Get &&
        ADL_Display_DisplayInfo_Get &&
        ADL_Display_EdidData_Get)
    {

      m_bOpen = (ADL_OK == ADL_Main_Control_Create(ADL_AllocMemory, 1));
    }
  }
}

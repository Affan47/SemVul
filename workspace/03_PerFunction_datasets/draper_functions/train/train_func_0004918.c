FreeDiskObject(struct DiskObject *diskobj)
{
  if(diskobj->do_Gadget.GadgetRender) free(diskobj->do_Gadget.GadgetRender);
  if(diskobj->do_Gadget.SelectRender) free(diskobj->do_Gadget.SelectRender);
  if(diskobj->do_DefaultTool) free(diskobj->do_DefaultTool);
  if(diskobj->do_ToolTypes) {
    char *p, **pp=diskobj->do_ToolTypes;
    while((p=*pp++)) free(p);
    free(diskobj->do_ToolTypes);
  }
  if(diskobj->do_DrawerData) free(diskobj->do_DrawerData);
  if(diskobj->do_ToolWindow) free(diskobj->do_ToolWindow);
  free(diskobj);
}

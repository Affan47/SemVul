printer_zxp_update_header(void)
{
long pos;

if(!printer_graphics_enabled || !zxpheight) return;

if(!printer_graphics_file && !printer_zxp_open_file())
  return;

pos=ftell(printer_graphics_file);


if(fseek(printer_graphics_file,strlen("P4\n256 "),SEEK_SET)!=0)
  ui_error(UI_ERROR_ERROR,
	   "Couldn't seek to write graphics printout image height");
else
  {


  fprintf(printer_graphics_file,"%10d",zxpheight);
  }

if(fseek(printer_graphics_file,pos,SEEK_SET)!=0)
  {
  ui_error(UI_ERROR_ERROR,
	   "Couldn't re-seek on file, graphics printout disabled");
  fclose(printer_graphics_file);
  printer_graphics_file=NULL;
  printer_graphics_enabled=0;
  }
}

DoExport(struct gfc_data *d,unichar_t *path) {
    char *temp;
    int format, good;

    temp = cu_copy(path);
    last_format = format = (intpt) (GGadgetGetListItemSelected(d->format)->userdata);
    if ( d->bc )
	last_format += BITMAP_FORMAT_START;
    if ( d->bc!=NULL )
	good = BCExportXBM(temp,d->bc,format);
    else if ( format==0 )
	good = ExportEPS(temp,d->sc,d->layer);
    else if ( format==1 )
	good = ExportFig(temp,d->sc,d->layer);
    else if ( format==2 )
	good = ExportSVG(temp,d->sc,d->layer);
    else if ( format==3 )
	good = ExportGlif(temp,d->sc,d->layer);
    else if ( format==4 )
	good = ExportPDF(temp,d->sc,d->layer);
    else if ( format==5 )
	good = ExportPlate(temp,d->sc,d->layer);
    else if ( format<fv_pythonbase )
	good = ExportXBM(temp,d->sc,d->layer,format-BITMAP_FORMAT_START);
#ifndef _NO_PYTHON
    else if ( format>=fv_pythonbase )
	PyFF_SCExport(d->sc,format-fv_pythonbase,temp,d->layer);
#endif
    if ( !good )
	ff_post_error(_("Save Failed"),_("Save Failed"));
    free(temp);
    d->done = good;
    d->ret = good;
}

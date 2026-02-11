oboinReadFmt(AjPOboin oboin, AjPObo obo,
                           ajuint format)
{
    ajDebug("++oboinReadFmt format %d (%s) '%S'\n",
	    format, oboinFormatDef[format].Name,
	    oboin->Input->Qry);

    oboin->Input->Records = 0;


    if((*oboinFormatDef[format].Read)(oboin, obo))
    {
	ajDebug("oboinReadFmt success with format %d (%s) '%S'\n",
		format, oboinFormatDef[format].Name, obo->Name);
	oboin->Input->Format = format;
	ajStrAssignC(&oboin->Input->Formatstr, oboinFormatDef[format].Name);
	ajStrAssignC(&obo->Formatstr, oboinFormatDef[format].Name);
	ajStrAssignEmptyS(&obo->Db, oboin->Input->Db);
	ajStrAssignS(&obo->Filename, oboin->Input->Filename);

	if(oboQueryMatch(oboin->Input->Query, obo))
	{


            return FMT_OK;
        }

	ajDebug("query match failed, continuing ...\n");
	ajOboClear(obo);

	return FMT_NOMATCH;
    }
    else
    {
	ajDebug("Testing input buffer: IsBuff: %B Eof: %B\n",
		ajFilebuffIsBuffered(oboin->Input->Filebuff),
		ajFilebuffIsEof(oboin->Input->Filebuff));

	if (!ajFilebuffIsBuffered(oboin->Input->Filebuff) &&
	    ajFilebuffIsEof(oboin->Input->Filebuff))
	    return FMT_EOF;

	ajFilebuffResetStore(oboin->Input->Filebuff,
                             oboin->Input->Text, &obo->TextPtr);
	ajDebug("Format %d (%s) failed, file buffer reset by oboinReadFmt\n",
		format, oboinFormatDef[format].Name);

    }

    ajDebug("++oboinReadFmt failed - nothing read\n");

    return FMT_FAIL;
}

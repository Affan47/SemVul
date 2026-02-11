get(SbString &fieldDataString, SoOutput *dictOut)


{
    const SoFieldData	*fieldData = getFieldData();

#ifdef DEBUG
    if (fieldData == NULL) {
	SoDebugError::post("SoFieldContainer::get",
			   "Field data is NULL!");
	return;
    }
#endif

    SoOutput	out(dictOut);


    if (fieldBufSize == 0) {
	fieldBufSize = 1028;
	fieldBuf = (char *) malloc((unsigned) fieldBufSize);
    }


    out.setBuffer((void *) fieldBuf, fieldBufSize,
		  &SoFieldContainer::reallocFieldBuf);


    out.setCompact(TRUE);


    SoBase::incrementCurrentWriteCounter();


    out.setStage(SoOutput::COUNT_REFS);
    getFieldData()->write(&out, this);


    out.setStage(SoOutput::WRITE);
    getFieldData()->write(&out, this);


    out.reset();


    fieldDataString = fieldBuf;
}

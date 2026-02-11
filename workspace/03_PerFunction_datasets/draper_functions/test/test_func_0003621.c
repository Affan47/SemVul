vStartOfListItemXML(diagram_type *pDiag, BOOL bNoMarks)
{
	const char	*szAttr;
	UCHAR	ucTopTag;

	fail(pDiag == NULL);

	if (bTableOpen) {

		return;
	}

	ucTopTag = ucReadStack();
	if (ucTopTag != TAG_ITEMIZEDLIST && ucTopTag != TAG_ORDEREDLIST) {

		vAddEndTagsUntil1(pDiag, TAG_LISTITEM);
	}

	DBG_DEC_C(ucReadStack() != TAG_ITEMIZEDLIST &&
		ucReadStack() != TAG_ORDEREDLIST, ucReadStack());


	szAttr = bNoMarks ? "override='none'" : NULL;
	vAddStartTag(pDiag, TAG_LISTITEM, szAttr);

	vAddStartTag(pDiag, TAG_PARA, NULL);
}

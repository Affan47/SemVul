pushOutlinesToPart(
    std::vector<QPDFObjectHandle>& part,
    std::set<QPDFObjGen>& lc_outlines,
    std::map<int, int> const& object_stream_data)
{
    QPDFObjectHandle root = getRoot();
    QPDFObjectHandle outlines = root.getKey("/Outlines");
    if (outlines.isNull())
    {
	return;
    }
    outlines = getUncompressedObject(outlines, object_stream_data);
    QPDFObjGen outlines_og(outlines.getObjGen());
    QTC::TC("qpdf", "QPDF lin outlines in part",
	    ((&part == (&this->part6)) ? 0
	     : (&part == (&this->part9)) ? 1
	     : 9999));
    this->c_outline_data.first_object = outlines_og.getObj();
    this->c_outline_data.nobjects = 1;
    lc_outlines.erase(outlines_og);
    part.push_back(outlines);
    for (std::set<QPDFObjGen>::iterator iter = lc_outlines.begin();
	 iter != lc_outlines.end(); ++iter)
    {
	part.push_back(objGenToIndirect(*iter));
	++this->c_outline_data.nobjects;
    }
}

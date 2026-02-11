dereference()
{
    if (this->obj.getPointer() == 0)
    {
        PointerHolder<QPDFObject> obj = QPDF::Resolver::resolve(
	    this->qpdf, this->objid, this->generation);
	if (obj.getPointer() == 0)
	{
	    QTC::TC("qpdf", "QPDFObjectHandle indirect to unknown");
	    this->obj = new QPDF_Null();
	}
        else if (dynamic_cast<QPDF_Reserved*>(obj.getPointer()))
        {

        }
        else
        {
            this->reserved = false;
            this->obj = obj;
        }
    }
}

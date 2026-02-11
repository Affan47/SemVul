setMethod(const QtSoapQName &meth)
{
    if (type != MethodRequest && type != OtherType) {
	clear();
	type = MethodRequest;
    }

    addBodyItem(new QtSoapStruct(meth));
}

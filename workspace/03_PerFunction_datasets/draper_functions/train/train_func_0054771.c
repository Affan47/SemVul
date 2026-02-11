encodeTypedObject(const cygnal::Element &data)
{


    size_t size = 0;
    boost::uint32_t props;
    props = data.propertySize();
    boost::shared_ptr<cygnal::Buffer> buf;

    if (props) {


	for (size_t i=0; i<data.propertySize(); i++) {
	    size += data.getProperty(i)->getDataSize();
	    size += data.getProperty(i)->getNameSize();
	    size += AMF_PROP_HEADER_SIZE;
	}
	size += data.getNameSize();
	buf.reset(new Buffer(size+24));
    }

    *buf = Element::TYPED_OBJECT_AMF0;

    size_t length = data.getNameSize();
    boost::uint16_t enclength = length;
    swapBytes(&enclength, 2);
    *buf += enclength;

    if (data.getName()) {
	std::string name = data.getName();
	if (name.size() > 0) {
	    *buf += name;
	}
    }

    if (data.propertySize() > 0) {
	std::vector<boost::shared_ptr<cygnal::Element> >::const_iterator ait;
	std::vector<boost::shared_ptr<cygnal::Element> > props = data.getProperties();
	for (ait = props.begin(); ait != props.end(); ait++) {
	    boost::shared_ptr<cygnal::Element> el = (*(ait));
	    boost::shared_ptr<cygnal::Buffer> item = AMF::encodeElement(el);
	    if (item) {
		*buf += item;
		item.reset();
	    } else {
		break;
	    }

	}
    }


    *buf += '\0';
    *buf += '\0';
    *buf += TERMINATOR;

    return buf;
}

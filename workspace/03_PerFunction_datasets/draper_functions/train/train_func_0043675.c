encodeDate(const boost::uint8_t *date)
{


    boost::shared_ptr<Buffer> buf;
    if (date != 0) {
	buf.reset(new Buffer(AMF0_NUMBER_SIZE+1));
	*buf = Element::DATE_AMF0;
	double num = *(reinterpret_cast<const double*>(date));
	swapBytes(&num, AMF0_NUMBER_SIZE);
	*buf += num;
    }
    return buf;
}

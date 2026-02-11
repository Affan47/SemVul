rad_attr2vp_wimax(const RADIUS_PACKET *packet,
			  const RADIUS_PACKET *original,
			  const char *secret,
			  const uint8_t *data,  size_t length,
			  VALUE_PAIR **pvp)
{
	ssize_t my_len;
	unsigned int attribute;
	uint32_t lvalue;

	if ((length < 2) || (data[1] < 2) || (data[1] > length)) {
		fr_strerror_printf("rad_attr2vp_wimax: Invalid length");
		return -1;
	}

	if (data[0] != PW_VENDOR_SPECIFIC) {
		fr_strerror_printf("rad_attr2vp_wimax: Invalid attribute");
		return -1;
	}


	if (data[1] < 9) {
		return rad_attr2vp_raw(packet, original, secret,
				       data, length, pvp);
	}

	memcpy(&lvalue, data + 2, 4);
	lvalue = ntohl(lvalue);


	if (lvalue != VENDORPEC_WIMAX) {
		DICT_VENDOR *dv;

		dv = dict_vendorbyvalue(lvalue);
		if (!dv || !dv->flags) {
			fr_strerror_printf("rad_attr2vp_wimax: Not a WiMAX attribute");
			return -1;
		}
	}


	if ((data[7] + 6) != data[1]) {
		return rad_attr2vp_raw(packet, original, secret,
				       data, length, pvp);
	}

	attribute = data[6];


	if (data[8] != 0) {
		my_len = wimax_attrlen(htonl(lvalue), data, data + length);
		if (my_len < 0) {
			return rad_attr2vp_raw(packet, original, secret,
					       data, length, pvp);
		}

		return data2vp_continued(packet, original, secret,
					 data, length, pvp, 0,
					 data[6], lvalue,
					 9, 9, my_len);
	}

	my_len = data2vp_any(packet, original, secret, 0, attribute, lvalue,
			     data + 9, data[1] - 9, pvp);
	if (my_len < 0) return my_len;

	return data[1];
}

wtp_pdu_type(Octstr *data) {
	long bitpos;
	long lastpos = -1;
	long lastnumbits = -1;
	long lastval = -1;
	int thistype;


#define PDU(name, docstring, fields, is_valid) \
	bitpos = 0; \
	thistype = name; \
	fields
#define UINT(field, docstring, bits) bitpos += (bits);
#define UINTVAR(field, docstring)
#define OCTSTR(field, docstring, lengthfield)
#define REST(field, docstring)
#define TYPE(bits, value) \
	if ((bits) != lastnumbits || bitpos != lastpos) { \
		lastval = octstr_get_bits(data, bitpos, (bits)); \
	} \
	if (lastval == (value)) \
		return thistype; \
	lastnumbits = (bits); \
	lastpos = bitpos;
#define RESERVED(bits) bitpos += (bits);
#define TPI(confield)
#include "wtp_pdu.def"
#undef TPI
#undef RESERVED
#undef TYPE
#undef REST
#undef OCTSTR
#undef UINTVAR
#undef UINT
#undef PDU

	return -1;
}

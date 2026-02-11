fixup_length_fields(WSP_PDU *pdu) {
	switch (pdu->type) {
#define PDU(name, docstring, fields, is_valid) \
	case name: { \
		struct name *p; p = &pdu->u.name; \
		fields \
	} break;
#define UINT(field, docstring, bits)
#define UINTVAR(field, docstring)
#define OCTSTR(field, docstring, lengthfield) \
	p->lengthfield = octstr_len(p->field);
#define REST(field, docstring)
#define TYPE(bits, value)
#define RESERVED(bits)
#include "wsp_pdu.def"
#undef RESERVED
#undef TYPE
#undef REST
#undef OCTSTR
#undef UINTVAR
#undef UINT
#undef PDU
	}
}

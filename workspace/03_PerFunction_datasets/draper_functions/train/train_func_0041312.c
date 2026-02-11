mime_type_to_string(enum mime_type type)
{
	static const char *names[] = {
#define MIME_TYPE(id, name) name,
#include "mime_types.h"
#undef MIME_TYPE
	};
	size_t i;

	STATIC_ASSERT(MIME_TYPE_NUM == G_N_ELEMENTS(names));
	i = (size_t) type < G_N_ELEMENTS(names)
			? type : MIME_TYPE_APPLICATION_OCTET_STREAM;
	return names[i];
}

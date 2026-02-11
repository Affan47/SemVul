cpl_propertylist_dump(const cpl_propertylist *self, FILE *stream)
{

    cxchar c = '\0';

    cpl_size i = 0;
    cpl_size sz = cpl_propertylist_get_size(self);


    if (stream == NULL)
        stream = stdout;

    if (self == NULL) {
        fprintf(stream, "NULL property list\n\n");
        return;
    }


    fprintf(stream, "Property list at address %p:\n", (cxcptr)self);

    for (i = 0; i < sz; i++) {
        const cpl_property *p = cpl_propertylist_get_const(self, i);
        const cxchar *name = cpl_property_get_name(p);
        const cxchar *comment = cpl_property_get_comment(p);
        cpl_size size = cpl_property_get_size(p);
        cpl_type type = cpl_property_get_type(p);
        const cxchar *typestr = cpl_type_get_name(type);

        fprintf(stream, "Property at address %p\n", (cxcptr)p);
        fprintf(stream, "\tname   : %p '%s'\n", name, name);
        fprintf(stream, "\tcomment: %p '%s'\n", comment, comment);
        fprintf(stream, "\ttype   : %#09x '%s'\n", type, typestr);
        fprintf(stream, "\tsize   : %ld\n", size);
        fprintf(stream, "\tvalue  : ");


        switch (type) {
        case CPL_TYPE_CHAR:
            c = cpl_property_get_char(p);
            if (!c)
                fprintf(stream, "''");
            else
                fprintf(stream, "'%c'", c);
            break;

        case CPL_TYPE_BOOL:
            fprintf(stream, "%d", cpl_property_get_bool(p));
            break;

        case CPL_TYPE_INT:
            fprintf(stream, "%d", cpl_property_get_int(p));
            break;

        case CPL_TYPE_LONG:
            fprintf(stream, "%ld", cpl_property_get_long(p));
            break;

        case CPL_TYPE_LONG_LONG:
            fprintf(stream, "%lld", cpl_property_get_long_long(p));
            break;

        case CPL_TYPE_FLOAT:
            fprintf(stream, "%.7g", cpl_property_get_float(p));
            break;

        case CPL_TYPE_DOUBLE:
            fprintf(stream, "%.15g", cpl_property_get_double(p));
            break;

        case CPL_TYPE_STRING:
            fprintf(stream, "'%s'", cpl_property_get_string(p));
            break;

        case CPL_TYPE_FLOAT_COMPLEX: {

            const float complex z = cpl_property_get_float_complex(p);
            fprintf(stream, "(%.7g,%.7g)", crealf(z), cimagf(z));
            break;
        }
        case CPL_TYPE_DOUBLE_COMPLEX: {

            const double complex z = cpl_property_get_double_complex(p);
            fprintf(stream, "(%.15g,%.15g)", creal(z), cimag(z));
            break;
        }
        default:
            fprintf(stream, "unknown.");
            break;

        }

        fprintf(stream, "\n");

    }

    return;

}

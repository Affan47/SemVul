fprint_pa_object_dim(FILE *fp, Pa_object *pa_object)
{
    int i;

    switch (pa_object->kind) {
    case KIND_VAR :
        break;
    case KIND_ARRAY :
        fprintf(fp, "(");
        for (i = 0; i < pa_object->tbl.a->dim; i++) {
            if (i != 0) fprintf(fp, ", ");
            fprintf(fp, "%d:%d",
                    pa_object->tbl.a->bas.ct[i],
                    pa_object->tbl.a->lim.ct[i]);
        }
        fprintf(fp, ")");
        break;
    case KIND_INVISIBLE :
        fprintf(fp, "(");
        for (i = 0; i < pa_object->tbl.i->dim; i++) {
            if (i != 0) fprintf(fp, ", ");
            fprintf(fp, "%d:%d",
                    pa_object->tbl.i->bas.ct[i],
                    pa_object->tbl.i->lim.ct[i]);
        }
        fprintf(fp, ")");
        break;
    case KIND_HEAP :
        fprintf(fp, "(");
        for (i = 0; i < pa_object->tbl.h->dim; i++) {
            if (i != 0) fprintf(fp, ", ");
            fprintf(fp, "%d:%d",
                    pa_object->tbl.h->bas.ct[i],
                    pa_object->tbl.h->lim.ct[i]);
        }
        fprintf(fp, ")");
        break;
    case KIND_SUB :
    case KIND_FUNC :
    case KIND_UNINIT :
    case KIND_UNKNOWN :
    case KIND_FILE :
    case KIND_TEMP :
	break;
    default :
	fatal("unexpected kind\n");
	break;
    }
}

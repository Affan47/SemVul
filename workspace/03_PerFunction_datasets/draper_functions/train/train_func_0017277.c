GC_print_obj(ptr_t p)
{
    oh * ohdr = (oh *)GC_base(p);
    ptr_t q;
    hdr * hhdr;
    int kind;
    char *kind_str;
    char buffer[GC_TYPE_DESCR_LEN + 1];

    GC_ASSERT(I_DONT_HOLD_LOCK());
#   ifdef LINT2
      if (!ohdr) ABORT("Invalid GC_print_obj argument");
#   endif

    q = (ptr_t)(ohdr + 1);


    hhdr = GC_find_header(q);
    kind = hhdr -> hb_obj_kind;
    if (0 != GC_describe_type_fns[kind] && GC_is_marked(ohdr)) {


        buffer[GC_TYPE_DESCR_LEN] = 0;
        (GC_describe_type_fns[kind])(q, buffer);
        GC_ASSERT(buffer[GC_TYPE_DESCR_LEN] == 0);
        kind_str = buffer;
    } else {
        switch(kind) {
          case PTRFREE:
            kind_str = "PTRFREE";
            break;
          case NORMAL:
            kind_str = "NORMAL";
            break;
          case UNCOLLECTABLE:
            kind_str = "UNCOLLECTABLE";
            break;
#         ifdef ATOMIC_UNCOLLECTABLE
            case AUNCOLLECTABLE:
              kind_str = "ATOMIC_UNCOLLECTABLE";
              break;
#         endif
          case STUBBORN:
            kind_str = "STUBBORN";
            break;
          default:
            kind_str = NULL;


        }
    }

    if (NULL != kind_str) {
        GC_err_printf("%p (%s:%d," IF_NOT_SHORTDBG_HDRS(" sz=%lu,") " %s)\n",
                      (ptr_t)ohdr + sizeof(oh),
                      ohdr->oh_string, GET_OH_LINENUM(ohdr)
                      COMMA_IFNOT_SHORTDBG_HDRS((unsigned long)ohdr->oh_sz),
                      kind_str);
    } else {
        GC_err_printf("%p (%s:%d," IF_NOT_SHORTDBG_HDRS(" sz=%lu,")
                      " kind=%d descr=0x%lx)\n", (ptr_t)ohdr + sizeof(oh),
                      ohdr->oh_string, GET_OH_LINENUM(ohdr)
                      COMMA_IFNOT_SHORTDBG_HDRS((unsigned long)ohdr->oh_sz),
                      kind, (unsigned long)hhdr->hb_descr);
    }
    PRINT_CALL_CHAIN(ohdr);
}

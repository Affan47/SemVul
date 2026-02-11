insn_data_to_s_detail(INSN *iobj)
{
    VALUE str = rb_sprintf("%-16s", insn_name(iobj->insn_id));

    if (iobj->operands) {
	const char *types = insn_op_types(iobj->insn_id);
	int j;

	for (j = 0; types[j]; j++) {
	    char type = types[j];
	    printf("str: %"PRIxVALUE", type: %c\n", str, type);

	    switch (type) {
	      case TS_OFFSET:
		{
		    LABEL *lobj = (LABEL *)OPERAND_AT(iobj, j);
		    rb_str_catf(str, "<L%03d>", lobj->label_no);
		    break;
		}
		break;
	      case TS_ISEQ:
		{
		    rb_iseq_t *iseq = (rb_iseq_t *)OPERAND_AT(iobj, j);
		    VALUE val = Qnil;
		    if (iseq) {
			val = iseq->self;
		    }
		    rb_str_concat(str, rb_inspect(val));
		}
		break;
	      case TS_LINDEX:
	      case TS_DINDEX:
	      case TS_NUM:
	      case TS_VALUE:
		rb_str_concat(str, rb_inspect(OPERAND_AT(iobj, j)));
		break;
	      case TS_ID:
		rb_str_concat(str, rb_inspect(OPERAND_AT(iobj, j)));
		break;
	      case TS_GENTRY:
		{
		    struct rb_global_entry *entry = (struct rb_global_entry *)
		      (OPERAND_AT(iobj, j) & (~1));
		    rb_str_cat2(str, rb_id2name(entry->id));
		}
	      case TS_IC:
		rb_str_catf(str, "<ic:%d>", FIX2INT(OPERAND_AT(iobj, j)));
		break;
	      case TS_CDHASH:
		rb_str_cat2(str, "<ch>");
		break;
	      default:{
		rb_raise(rb_eSyntaxError, "unknown operand type: %c", type);
	      }
	    }
	    if (types[j + 1]) {
		rb_str_cat2(str, ", ");
	    }
	}
    }
    return str;
}

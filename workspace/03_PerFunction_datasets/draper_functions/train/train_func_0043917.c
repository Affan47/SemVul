rb_iseq_disasm_insn(VALUE ret, VALUE *iseq, size_t pos,
		    rb_iseq_t *iseqdat, VALUE child)
{
    VALUE insn = iseq[pos];
    int len = insn_len(insn);
    int j;
    const char *types = insn_op_types(insn);
    VALUE str = rb_str_new(0, 0);
    const char *insn_name_buff;

    insn_name_buff = insn_name(insn);
    if (1) {
	rb_str_catf(str, "%04"PRIdSIZE" %-16s ", pos, insn_name_buff);
    }
    else {
	rb_str_catf(str, "%04"PRIdSIZE" %-16.*s ", pos,
		    (int)strcspn(insn_name_buff, "_"), insn_name_buff);
    }

    for (j = 0; types[j]; j++) {
	const char *types = insn_op_types(insn);
	VALUE opstr = insn_operand_intern(iseqdat, insn, j, iseq[pos + j + 1],
					  len, pos, &iseq[pos + j + 2],
					  child);
	rb_str_concat(str, opstr);

	if (types[j + 1]) {
	    rb_str_cat2(str, ", ");
	}
    }

    if (1) {
	int line_no = find_line_no(iseqdat, pos);
	int prev = find_prev_line_no(iseqdat, pos);
	if (line_no && line_no != prev) {
	    long slen = RSTRING_LEN(str);
	    slen = (slen > 70) ? 0 : (70 - slen);
	    str = rb_str_catf(str, "%*s(%4d)", (int)slen, "", line_no);
	}
    }
    else {

	struct iseq_insn_info_entry *entry = get_insn_info(iseqdat, pos);
	long slen = RSTRING_LEN(str);
	slen = (slen > 60) ? 0 : (60 - slen);
	str = rb_str_catf(str, "%*s(line: %d, sp: %d)",
			  (int)slen, "", entry->line_no, entry->sp);
    }

    if (ret) {
	rb_str_cat2(str, "\n");
	rb_str_concat(ret, str);
    }
    else {
	printf("%s\n", RSTRING_PTR(str));
    }
    return len;
}

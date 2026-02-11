make_attribute(void)
{   int i; char *name;

 if (!glulx_mode) {
    if (no_attributes==((version_number==3)?32:48))
    {   if (version_number==3)
            error("All 32 attributes already declared (compile as Advanced \
game to get an extra 16)");
        else
            error("All 48 attributes already declared");
        panic_mode_error_recovery(); return;
    }
 }
 else {
    if (no_attributes==NUM_ATTR_BYTES*8) {
      error_numbered(
        "All attributes already declared -- increase NUM_ATTR_BYTES to use \
more than",
        NUM_ATTR_BYTES*8);
      panic_mode_error_recovery();
      return;
    }
 }

    get_next_token();
    i = token_value; name = token_text;
    if ((token_type != SYMBOL_TT) || (!(sflags[i] & UNKNOWN_SFLAG)))
    {   ebf_error("new attribute name", token_text);
        panic_mode_error_recovery(); return;
    }

    directive_keywords.enabled = TRUE;
    get_next_token();
    directive_keywords.enabled = FALSE;

    if ((token_type == DIR_KEYWORD_TT) && (token_value == ALIAS_DK))
    {   get_next_token();
        if (!((token_type == SYMBOL_TT)
              && (stypes[token_value] == ATTRIBUTE_T)))
        {   ebf_error("an existing attribute name after 'alias'",
                token_text); panic_mode_error_recovery(); return;
        }
        assign_symbol(i, svals[token_value], ATTRIBUTE_T);
        sflags[token_value] |= ALIASED_SFLAG;
        sflags[i] |= ALIASED_SFLAG;
    }
    else
    {   assign_symbol(i, no_attributes++, ATTRIBUTE_T);
        put_token_back();
    }

    trace_s(name, svals[i], 0);
    return;
}

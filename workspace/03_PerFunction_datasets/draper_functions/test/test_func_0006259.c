builtin_define_with_hex_fp_value (const char *macro,
				  tree type, int digits,
				  const char *hex_str,
				  const char *fp_suffix,
				  const char *fp_cast)
{
  REAL_VALUE_TYPE real;
  char dec_str[64], buf1[256], buf2[256];


  if (lazy_hex_fp_value_count < 12
      && flag_dump_macros == 0
      && !cpp_get_options (parse_in)->traditional)
    {
      struct cpp_hashnode *node;
      if (lazy_hex_fp_value_count == 0)
	cpp_get_callbacks (parse_in)->user_builtin_macro = lazy_hex_fp_value;
      sprintf (buf2, fp_cast, "1.1");
      sprintf (buf1, "%s=%s", macro, buf2);
      cpp_define (parse_in, buf1);
      node = C_CPP_HASHNODE (get_identifier (macro));
      lazy_hex_fp_values[lazy_hex_fp_value_count].hex_str
	= ggc_strdup (hex_str);
      lazy_hex_fp_values[lazy_hex_fp_value_count].mode = TYPE_MODE (type);
      lazy_hex_fp_values[lazy_hex_fp_value_count].digits = digits;
      lazy_hex_fp_values[lazy_hex_fp_value_count].fp_suffix = fp_suffix;
      lazy_hex_fp_values[lazy_hex_fp_value_count].macro = node->value.macro;
      node->flags |= NODE_BUILTIN;
      node->value.builtin
	= (enum cpp_builtin_type) (BT_FIRST_USER + lazy_hex_fp_value_count);
      lazy_hex_fp_value_count++;
      return;
    }


  real_from_string (&real, hex_str);
  real_to_decimal_for_mode (dec_str, &real, sizeof (dec_str), digits, 0,
			    TYPE_MODE (type));


  sprintf (buf1, "%s%s", dec_str, fp_suffix);
  sprintf (buf2, fp_cast, buf1);
  sprintf (buf1, "%s=%s", macro, buf2);

  cpp_define (parse_in, buf1);
}

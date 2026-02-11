Syntax_Error_Info_4(WamWord file_name_word,
		    WamWord line_word, WamWord char_word, WamWord msg_word)
{
  Check_For_Un_Atom(file_name_word);
  Check_For_Un_Integer(line_word);
  Check_For_Un_Integer(char_word);
  Check_For_Un_Atom(msg_word);

  return last_err_file &&
    Un_String(last_err_file, file_name_word) &&
    Un_Integer(last_err_line, line_word) &&
    Un_Integer(last_err_col, char_word) &&
    Un_String(last_err_msg, msg_word);
}

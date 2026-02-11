mpegts_parse_program_stopped (MpegTSBase * base, MpegTSBaseProgram * program)
{
  MpegTSParse2 *parse = GST_MPEGTS_PARSE (base);
  MpegTSParseProgram *parseprogram = (MpegTSParseProgram *) program;
  MpegTSParsePad *tspad;


  tspad = find_pad_for_program (parse, program->program_number);

  if (tspad) {
    tspad->program = NULL;
    parseprogram->tspad = NULL;
  }
}

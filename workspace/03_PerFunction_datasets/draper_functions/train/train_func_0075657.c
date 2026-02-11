mfs_lower_load_token(ErlDrvTermData TokenTag, int is_empty,
                                 yyscan_t yyscanner)
#else
static void mfs_lower_load_token(ErlDrvTermData TokenTag, int is_empty)
#endif
{

  int i;
#if defined(MEGACO_REENTRANT_FLEX_SCANNER)
  struct yyguts_t * yyg = (struct yyguts_t*)yyscanner;
  MfsErlDrvData* dataP = (MfsErlDrvData*) megaco_flex_scanner_drv_mtget_extra(yyscanner);
#else
  MfsErlDrvData* dataP = &mfs_drv_data;
#endif

  DBG( ("mfs_lower_load_token -> entry with"
	"\n   TokenTag: %ld"
	"\n   is_empty: %d"
        "\n", TokenTag, is_empty) );

  mfs_ensure_term_spec(dataP, 9);
  dataP->token_counter++;
  ASSIGN_TERM_SPEC(dataP, ERL_DRV_ATOM);
  ASSIGN_TERM_SPEC(dataP, TokenTag);
  ASSIGN_TERM_SPEC(dataP, ERL_DRV_INT);
  ASSIGN_TERM_SPEC(dataP, LINENO_OR_TOKENCNT(dataP));
  ASSIGN_TERM_SPEC(dataP, ERL_DRV_STRING);

  if (is_empty) {

    ASSIGN_TERM_SPEC(dataP, (ErlDrvTermData)"");
    ASSIGN_TERM_SPEC(dataP, 0);

  } else {
    for ( i = 0; i < yyleng; ++i ) {
      dataP->text_ptr[i] = tolower(yytext[i]);
    }

    DBG_BUF("mfs_lower_load_token", "dataP->text_ptr",
             dataP->text_ptr, yyleng);

    ASSIGN_TERM_SPEC(dataP, (ErlDrvTermData) dataP->text_ptr);
    dataP->text_ptr += yyleng;
    ASSIGN_TERM_SPEC(dataP, yyleng);
  }

  ASSIGN_TERM_SPEC(dataP, ERL_DRV_TUPLE);
  ASSIGN_TERM_SPEC(dataP, 3);
}

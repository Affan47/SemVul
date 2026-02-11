cmListFileLexer_yylex_destroy  (yyscan_t yyscanner)
{
    struct yyguts_t * yyg = (struct yyguts_t*)yyscanner;


        while(YY_CURRENT_BUFFER){
                cmListFileLexer_yy_delete_buffer(YY_CURRENT_BUFFER ,yyscanner );
                YY_CURRENT_BUFFER_LVALUE = NULL;
                cmListFileLexer_yypop_buffer_state(yyscanner);
        }


        cmListFileLexer_yyfree(yyg->yy_buffer_stack ,yyscanner);
        yyg->yy_buffer_stack = NULL;


        cmListFileLexer_yyfree(yyg->yy_start_stack ,yyscanner );
        yyg->yy_start_stack = NULL;


    yy_init_globals( yyscanner);


    cmListFileLexer_yyfree ( yyscanner , yyscanner );
    return 0;
}
